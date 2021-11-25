import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stock_symbols = [
        stock["symbol"]
        for stock in db.execute(
            "SELECT DISTINCT symbol FROM purchases WHERE user_id = ?",
            session["user_id"],
        )
    ]
    purchases = db.execute(
        """
            SELECT symbol, name, SUM(shares) AS shares, SUM(purchase_price) AS price
            FROM purchases
            WHERE user_id = ?
            GROUP BY symbol;
        """,
        session["user_id"],
    )

    purchase_map = {
        purchase["symbol"]: {
            "name": purchase["name"],
            "shares": purchase["shares"],
            "price": purchase["price"]
        }
        for purchase in purchases
    }

    sales = db.execute(
        """
            SELECT symbol, name, SUM(shares) AS shares, SUM(price) AS price
            FROM sales
            WHERE user_id = ?
            GROUP BY symbol;
        """,
        session["user_id"],
    )
    sale_map = {
        sale["symbol"]: {
            "name": sale["name"],
            "shares": sale["shares"],
            "price": sale["price"]
        }
        for sale in sales
    }

    asset_total = 0
    stocks = []
    for symbol in stock_symbols:
        share_count = (
            purchase_map[symbol]["shares"] - (
                sale_map.get(symbol, {}).get("shares") or 0
            )
        )
        if share_count > 0:
            purchase_total = purchase_map[symbol]["price"] * share_count
            stock = lookup(symbol)
            stocks.append(
                {
                    "symbol": symbol,
                    "name": stock["name"],
                    "price": usd(stock["price"]),
                    "shares": share_count,
                    "total": usd(purchase_total),
                }
            )
            asset_total += purchase_total

    user_cash = db.execute(
        "SELECT cash FROM users WHERE id = ?", session["user_id"]
    )[0]["cash"]

    user = {
        "cash": usd(user_cash),
        "total": usd(user_cash + asset_total),
    }
    return render_template("index.html", stocks=stocks, user=user)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    stock = lookup(request.form.get("symbol"))
    if stock is None:
        return apology("invalid symbol", 400)

    try:
        shares = int(request.form.get("shares"))
    except ValueError:
        return apology("shares must be a positive integer", 400)

    if shares < 0:
        return apology("shares must be a positive integer", 400)

    current_cash = db.execute(
        "SELECT cash FROM users WHERE id = ?", session["user_id"]
    )[0]["cash"]

    db.execute(
        """
            INSERT INTO purchases (
                symbol,
                name,
                user_id,
                purchase_price,
                shares,
                created_at
            )
            VALUES (?, ?, ?, ?, ?, ?);
        """,
        stock["symbol"],
        stock["name"],
        session["user_id"],
        stock["price"],
        request.form.get("shares"),
        datetime.now().timestamp(),
    )
    db.execute(
        "UPDATE users SET cash = ? WHERE id = ?",
        current_cash - (stock["price"] * int(request.form.get("shares"))),
        session["user_id"],
    )
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    if not request.form.get("symbol"):
        return apology("missing symbol", 400)

    stock = lookup(request.form.get("symbol"))
    if stock is None:
        return apology("invalid symbol", 400)

    return render_template(
        "quoted.html",
        symbol=stock["symbol"],
        name=stock["name"],
        price=usd(stock["price"]),
    )


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        password = request.form.get("password")
        if not password:
            return apology("must provide password", 400)

        # Ensure password is confirmed
        confirmation = request.form.get("confirmation")
        if not confirmation or (password != confirmation):
            return apology("password and confirmation must match", 400)

        # Ensure the username is unique
        existing_user = db.execute("SELECT * FROM users WHERE username = ?", username)
        if existing_user:
            return apology(f"user with username {username} already exists", 400)

        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            request.form.get("username"),
            generate_password_hash(request.form.get("password")),
        )
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        stocks = db.execute(
            "SELECT name, symbol FROM purchases WHERE user_id = ?",
            session["user_id"],
        )
        return render_template("sell.html", stocks=stocks)

    try:
        shares = int(request.form.get("shares"))
    except ValueError:
        return apology("shares must be a positive integer", 400)

    if not shares:
        return apology("must include shares", 400)

    symbol = request.form.get("symbol")
    if not symbol:
        return apology("symbol is required", 400)

    stock = db.execute(
        """
            SELECT
                symbol,
                shares
            FROM purchases
            WHERE user_id = ?
            AND symbol = ?
        """,
        session["user_id"],
        request.form.get("symbol"),
    )[0]
    if shares > stock["shares"]:
        return apology("shares can't exceed purchased amount", 400)

    current_stock = lookup(stock["symbol"])
    db.execute(
        """
            INSERT INTO sales (
                symbol,
                name,
                user_id,
                price,
                shares,
                created_at
            )
            VALUES (?, ?, ?, ?, ?, ?);
        """,
        current_stock["symbol"],
        current_stock["name"],
        session["user_id"],
        current_stock["price"],
        request.form.get("shares"),
        datetime.now().timestamp(),
    )
    current_cash = db.execute(
        "SELECT cash FROM users WHERE id = ?", session["user_id"]
    )[0]["cash"]
    db.execute(
        "UPDATE users SET cash = ? WHERE id = ?",
        current_cash + (current_stock["price"] * shares),
        session["user_id"],
    )
    return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

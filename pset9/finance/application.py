import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

import validations
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
    # Get all the stock symbols this user has boughts
    stock_symbols = [
        stock["symbol"]
        for stock in db.execute(
            "SELECT DISTINCT symbol FROM purchases WHERE user_id = ?",
            session["user_id"],
        )
    ]
    # Collect all their purchases
    purchases = db.execute(
        """
            SELECT symbol, SUM(shares) AS shares
            FROM purchases
            WHERE user_id = ?
            GROUP BY symbol;
        """,
        session["user_id"],
    )
    purchase_map = {purchase["symbol"]: purchase["shares"] for purchase in purchases}

    asset_total = 0
    stocks = []
    for symbol in stock_symbols:
        sales_count = 0
        # Get all the sales this user made of the stock
        sales_rows = db.execute(
            """
                SELECT SUM(shares) AS shares
                FROM sales
                WHERE user_id = ?
                AND symbol = ?;
            """,
            session["user_id"],
            symbol,
        )
        # ensure there are any to subtract
        if sales_rows:
            sales_count = sales_rows[0]["shares"] or 0

        share_count = purchase_map[symbol] - sales_count
        # ensure the user still has some shares
        if share_count > 0:
            stock = lookup(symbol)
            holding_total = stock["price"] * share_count
            stocks.append(
                {
                    "symbol": symbol,
                    "name": stock["name"],
                    "price": stock["price"],
                    "shares": share_count,
                    "total": holding_total,
                }
            )
            # keep track of the running total value
            asset_total += holding_total

    user_cash = db.execute(
        "SELECT cash FROM users WHERE id = ?", session["user_id"]
    )[0]["cash"]

    user = {
        "cash": user_cash,
        "total": user_cash + asset_total,
    }
    return render_template("index.html", stocks=stocks, user=user)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    error, stock = validations.validate_buy(
        request.form, lookup(request.form.get("symbol"))
    )
    if error:
        return error

    current_cash = db.execute(
        "SELECT cash FROM users WHERE id = ?", session["user_id"]
    )[0]["cash"]

    # ensure the user can afford the stocks
    if current_cash < (stock["price"] * int(request.form.get("shares"))):
        return apology("not enough cash for this transaction", 400)

    # log the purchase
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
    # update their cash
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
    transactions = db.execute(
        """
            SELECT
                symbol,
                shares,
                purchase_price AS price,
                created_at
            FROM purchases
            UNION ALL
            SELECT
                symbol,
                -shares,
                price,
                created_at
            FROM sales
            ORDER BY created_at;
        """
    )
    stocks = [
        {
            "symbol": transaction["symbol"],
            "shares": transaction["shares"],
            "price": transaction["price"],
            "transacted": datetime.fromtimestamp(
                transaction["created_at"]
            ).strftime("%Y-%m-%d %H:%M:%S"),
        }
        for transaction in transactions
    ]
    return render_template("history.html", stocks=stocks)


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

    error, stock = validations.validate_quote(
        request.form, lookup(request.form.get("symbol"))
    )
    if error:
        return error

    return render_template(
        "quoted.html",
        symbol=stock["symbol"],
        name=stock["name"],
        price=stock["price"],
    )


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        error = validations.validate_registration(request.form, db)
        if error:
            return error

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
        purchases = db.execute(
            """
                SELECT symbol, name, SUM(shares) AS shares
                FROM purchases
                WHERE user_id = ?
                GROUP BY symbol
                ORDER BY name;
            """,
            session["user_id"],
        )
        sales = db.execute(
            """
                SELECT symbol, SUM(shares) AS shares
                FROM sales
                WHERE user_id = ?
                GROUP BY symbol;
            """,
            session["user_id"],
        )
        sales_map = {sale["symbol"]: sale["shares"] for sale in sales}
        stocks = [
            {"symbol": purchase["symbol"], "name": purchase["name"]}
            for purchase in purchases
            if (purchase["shares"] - sales_map.get(purchase["symbol"], 0)) > 0
        ]

        return render_template("sell.html", stocks=stocks)

    error = validations.validate_sale(request.form, db, session)
    if error:
        return error

    current_stock = lookup(request.form["symbol"])
    shares = int(request.form["shares"])
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
        shares,
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

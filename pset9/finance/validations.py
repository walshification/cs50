import re

from helpers import apology


def validate_registration(form, db):
    """Validate the arguments of a registration form."""
    # Ensure username was submitted
    username = form.get("username")
    if not username:
        return apology("must provide username", 400)

    # Ensure password was submitted
    password = form.get("password")
    if not password:
        return apology("must provide password", 400)

    if not re.search(r"[!@#$%^&*)(.,;:'~]+", password):
        return apology("password must contain at least one special character", 400)

    if not re.search(r"[0-9]+", password):
        return apology("password must contain at least one number", 400)

    # Ensure password is confirmed
    confirmation = form.get("confirmation")
    if not confirmation or (password != confirmation):
        return apology("password and confirmation must match", 400)

    # Ensure the username is unique
    existing_user = db.execute("SELECT * FROM users WHERE username = ?", username)
    if existing_user:
        return apology(f"user with username {username} already exists", 400)


def validate_quote(form, stock):
    """Validate the arguments of a quote form."""
    if not form.get("symbol"):
        return apology("missing symbol", 400), stock

    if stock is None:
        return apology("invalid symbol", 400), stock

    return None, stock


def validate_buy(form, stock):
    """Validate the arguments of a buy form."""
    if stock is None:
        return apology("invalid symbol", 400), stock

    try:
        shares = int(form.get("shares"))
    except ValueError:
        return apology("shares must be a positive integer", 400), stock

    if shares < 0:
        return apology("shares must be a positive integer", 400), stock

    return None, stock


def validate_sale(form, db, session):
    """Validate the arguments of a sell form."""
    try:
        shares = int(form.get("shares"))
    except ValueError:
        return apology("shares must be a positive integer", 400)

    if not shares:
        return apology("must include shares", 400)

    symbol = form.get("symbol")
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
        form.get("symbol"),
    )[0]
    if shares > stock["shares"]:
        return apology("shares can't exceed purchased amount", 400)

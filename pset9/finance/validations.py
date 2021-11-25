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

    # Ensure password is confirmed
    confirmation = form.get("confirmation")
    if not confirmation or (password != confirmation):
        return apology("password and confirmation must match", 400)

    # Ensure the username is unique
    existing_user = db.execute("SELECT * FROM users WHERE username = ?", username)
    if existing_user:
        return apology(f"user with username {username} already exists", 400)

from model.database import db
from helpers import apology, login_required, lookup, usd
from werkzeug.security import check_password_hash, generate_password_hash


def get_user_by_id(user_id):
    users = db.execute("SELECT * FROM users WHERE id = ?", user_id)
    if len(users) > 0:
        return users[0]
    else:
        return None


def get_user_by_username_and_password(username, password):

    # Query database for username
    rows = db.execute("SELECT * FROM users WHERE username = ?", username)

    # Ensure username exists and password is correct
    if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
        return None
    else:
        return rows[0]


def register(username, password):
    hashed_password = generate_password_hash(password)

    new_user = db.execute(
        "INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed_password)

    return new_user


def add_cash(user_id, amount):
    user = get_user_by_id(user_id)
    update_cash = user["cash"] + amount
    db.execute("UPDATE users SET cash = ? WHERE id = ?",
               update_cash, user_id)

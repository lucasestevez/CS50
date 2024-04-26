from model.database import db


def get_balances_by_user_id(user_id):
    rows = db.execute(
        "SELECT * FROM balances WHERE user_id = ?", user_id)

    return rows


def get_positive_stocks(user_id):
    rows = db.execute(
        "SELECT * FROM balances WHERE user_id = ? AND shares > 0", user_id)
    return rows


def sell_user_shares(user_id, symbol, shares):
    balances = db.execute(
        "SELECT * FROM balances WHERE user_id = ? and symbol = ?", user_id, symbol)

    if len(balances) < 1:
        return False, f"insufficient shares"

    balance = balances[0]

    if shares > balance["shares"]:
        return False, f"insufficient shares"

    balance['shares'] -= shares
    db.execute("UPDATE balances SET shares = ? WHERE id = ?",
               balance['shares'], balance["id"])

    return True, None


def buy_shares(user_id, symbol, shares):
    rows = db.execute(
        "SELECT * FROM balances WHERE user_id = ? AND symbol = ?", user_id, symbol)

    if len(rows) < 1:
        db.execute("INSERT INTO balances (user_id, symbol, shares) VALUES (?, ?, ?)",
                   user_id, symbol, shares)
    else:
        balance = rows[0]
        balance["shares"] += shares
        db.execute("UPDATE balances SET shares = ? WHERE id = ?",
                   balance["shares"], balance["id"])

    return True, None

from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from helpers import apology, login_required, lookup, usd
from model import database, users, history as history_db, balances

db = database.db

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user = users.get_user_by_id(session["user_id"])

    rows = balances.get_balances_by_user_id(user["id"])

    stocks = []
    for row in rows:

        stock = lookup(row['symbol'])

        row['price'] = stock['price']
        row['total'] = stock['price'] * row['shares']
        row['name'] = stock['name']
        stocks.append(row)

    return render_template("index.html", cash=user['cash'], balances=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if not symbol:
            flash("must provide a stock symbol", 'danger')
            return render_template("buy.html")

        symbol = symbol.upper()
        stock = lookup(symbol)

        if not stock:
            flash(f"invalid stock '{symbol}'", 'danger')
            return render_template("buy.html")

        elif shares < 1:
            flash("must provide positivy quantity of shares", 'danger')
            return render_template("buy.html")

        total = stock["price"] * shares

        user = users.get_user_by_id(session['user_id'])
        if user['cash'] < total:
            flash(f"insuficient balance", 'danger')
            return render_template("buy.html")

        success, message = balances.buy_shares(session["user_id"], symbol, shares)
        if not success:
            return apology(message, 400)

        history_db.insert_new_entry(session['user_id'], symbol, shares, stock["price"])

        users.add_cash(session["user_id"], -stock['price'] * shares)

        flash(f"brougth '{shares}' of '{symbol}' successfuly", 'success')
        return redirect("/")

    else:

        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = history_db.get_history_by_user_id(session["user_id"])

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        # Ensure username was submitted
        if not username:
            flash("must provide username", 'danger')
            return render_template("login.html")

        # Ensure password was submitted
        elif not password:
            flash("must provide password", 'danger')
            return render_template("login.html")

        user = users.get_user_by_username_and_password(username, password)

        if not user:
            flash("invalid username and/or password", 'danger')
            return render_template("login.html")

        # Remember which user has logged in
        session["user_id"] = user["id"]

        flash(f"login successfuly", 'success')
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

    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            flash("must provide a stock symbol", 'danger')
            return render_template("quote.html")

        stock = lookup(symbol)

        if not stock:
            flash(f"invalid stock '{symbol}'", 'danger')
            return render_template("quote.html")

        return render_template("quoted.html", stock=stock)

    else:

        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    username = request.form.get("username")
    password = request.form.get("password")
    confirm_password = request.form.get("confirm_password")

    if request.method == "POST":

     # Ensure username was submitted
        if not username:
            flash("must provide username", 'danger')
            return render_template("register.html")

        # Ensure password was submitted
        elif not password:
            flash("must provide password", 'danger')
            return render_template("register.html")

        elif confirm_password != password:
            flash("passwords don't match", 'danger')
            return render_template("register.html")

        new_user = users.register(username, password)

        session["user_id"] = new_user
        flash(f"Registered", 'success')

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if shares < 1:
            flash("must provide positivy quantity of shares", 'danger')
            return render_template("sell.html")

        if not symbol:
            flash("must a stock symbol", 'danger')
            return render_template("sell.html")

        stock = lookup(symbol)
        if not stock:
            flash(f"error retrieving stock", 'danger')
            return render_template("sell.html")

        symbol = symbol.upper()

        success, message = balances.sell_user_shares(session["user_id"], symbol, shares)
        if not success:
            return apology(message, 400)

        history_db.insert_new_entry(session['user_id'], symbol, shares * -1, stock["price"])

        users.add_cash(session["user_id"], stock['price'] * shares)

        flash(f"brougth '{shares}' of '{symbol}' successfuly", 'success')
        return redirect("/")

    else:
        stocks = balances.get_positive_stocks(session["user_id"])
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

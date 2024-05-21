import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

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


@app.route("/")
@login_required
def index():

    userid = session["user_id"]

    tposition = db.execute("SELECT symbol, SUM(shares) AS 'shares' FROM transactions WHERE user_id=? GROUP BY symbol HAVING sum(shares) > 0 ORDER BY symbol", userid)
    cash = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])[0]

    listb = []
    totalbuy = 0

    for j in tposition:
        rlook = lookup(j['symbol'])
        total = rlook['price'] * float(j['shares'])
        totalbuy += total
        listb.append(
            {
                'symbol': j['symbol'],
                'name': rlook['name'],
                'shares': j['shares'],
                'price': rlook['price'],
                'total': total
            }
        )

    totalbuy += cash['cash']

    return render_template('index.html', table=listb, cash=cash['cash'], total=totalbuy)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Missing symbol", 400)
        elif not request.form.get("shares"):
            return apology("Missing shares", 400)

        shares = int(request.form.get("shares"))
        rlook = lookup(request.form.get("symbol"))
        cash = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])[0]

        if rlook == None:
            return apology("Invalid symbol", 400)
        if cash['cash'] < (rlook['price'] * shares):
            return apology("Can't Afford", 400)

        db.execute("INSERT INTO transactions (user_id, symbol, price, shares) VALUES (?, ?, ?, ?);", session["user_id"], rlook['symbol'], rlook['price'], shares)
        expense = cash['cash'] - (rlook['price'] * shares)
        db.execute("UPDATE users SET cash=? WHERE id=?;", expense, session["user_id"])

        flash('Bought!')
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    userid = session["user_id"]
    table = db.execute("SELECT * FROM transactions WHERE user_id=? ORDER BY date DESC", userid)
    return render_template("history.html", table=table)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

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
    if request.method == "POST":
        rlook = lookup(request.form.get("symbol"))

        if rlook == None:
            return apology("Invalid symbol", 400)

        message = "A share of " + rlook["name"] + " (" + rlook["symbol"] + ") " + "costs " + usd(rlook["price"]) + "."
        return render_template("quoted.html", message=message)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        users = db.execute("SELECT * FROM users WHERE username=?", request.form.get("username"))
        # Tratamento de erro
        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif len(users) > 0:
            return apology("Username not available")

        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password don't match", 400)

        # Query insert user
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Redirect to login
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        tposition = db.execute("SELECT symbol, SUM(shares) AS 'shares' FROM transactions WHERE user_id=? AND symbol=? GROUP BY symbol HAVING sum(shares) > 0 ORDER BY symbol", session["user_id"], symbol)[0]

        if tposition['shares'] < int(shares):
            return apology("Too many shares", 400)

        rlook = lookup(symbol)
        seller = rlook['price'] * float(shares)

        nshares = shares * (-1)
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares) VALUES (?, ?, ?, ?);", session["user_id"], symbol, rlook['price'], nshares)
        cash = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])[0]
        expense = cash['cash'] + seller
        db.execute("UPDATE users SET cash=? WHERE id=?;", expense, session["user_id"])

        flash('Sold!')
        return redirect("/")

    else:
        userid = session["user_id"]
        tposition = db.execute("SELECT symbol, SUM(shares) AS 'shares' FROM transactions WHERE user_id=? GROUP BY symbol HAVING sum(shares) > 0 ORDER BY symbol", userid)
        return render_template("sell.html", tposition=tposition)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

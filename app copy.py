import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime, timezone

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    owns = own_shares()
    total = 0

    for symbol, shares in owns.items():
        result = lookup(symbol)
        name, price = result["name"], result["price"]
        stock_value = shares * price
        total += stock_value
        owns[symbol] = (name, shares, usd(price), usd(stock_value))

    cash = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])[0]['cash']
    total += cash

    return render_template("index.html", owns=owns, cash= usd(cash), total = usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached request via GET
    if request.method == "GET":
        return render_template("buy.html")

    # User reached request via POST
    else:

        # Create variables for user input
        symbol = request.form.get("symbol")
        numShare = request.form.get("shares")

        # Validate user input
        if symbol == "" or numShare == "" or lookup(symbol) == None or numShare[0] == "-":
            return apology("invalid symbol or share number", 400)

        # Calculate total price of the shares
        quote = lookup(symbol)
        sharePrice = int(quote["price"])
        totalPrice = sharePrice * int(numShare)

        # Validate if user can afford the amount of shares
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
        if totalPrice > int(cash):
            return apology("you can't afford this", 400)

        # Proceed with transaction if user can afford the share
        else:

            # Insert transaction information into finance.db
            db.execute("INSERT INTO purchases(shareSymbol, pricePerShare, user_id, totalPrice, numShares, timestamp) VALUES(?, ?, ?, ?, ?, ?)",
                        symbol, sharePrice, user_id, totalPrice, numShare, time_now())

            # Update amount of cash in user's account
            newCashAmount = int(cash) - totalPrice
            db.execute("UPDATE users SET cash = ? WHERE id = ?", newCashAmount, user_id)

        # Redirect to Homepage
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT shareSymbol, numShares, pricePerShare, timestamp FROM purchases WHERE user_id = ?",
                        session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/addCash", methods=["GET", "POST"])
@login_required
def addCash():

    if request.method == "GET":
        return render_template("addCash.html")

    else:
        userID = session["user_id"]
        cashAMT = request.form.get("cash")
        originalAMT = db.execute("SELECT cash FROM users WHERE id = ?", userID)
        newAMT = int(originalAMT) + int(cashAMT[0])
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newAMT, userID)


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
    # Render template when the user reaches route via GET
    if request.method == "GET":
        return render_template("quote.html")

    # User reached route via POST
    else:

        # Create variable for Symbol
        symbol = request.form.get("symbol")

        # Validate user input
        if symbol == "":
            return apology("must provide symbol", 400)

        # Lookup the quote for the symbol
        else:
            data = lookup(symbol)

            if data == None:
                return apology("invalid symbol", 400)
            else:
                price = usd(data["price"])
                return render_template("quoted.html", data=data, price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Create variables with new username and password
        newUsername = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check input of username
        if newUsername == "":
            return apology("must provide username", 400)

        elif len(db.execute("SELECT * FROM users WHERE username = ?", newUsername)) == 1:
            return apology("username already in use", 400)

        # Check input of password
        if password == "":
            return apology("must provide password", 400)

        elif confirmation == "":
            return apology("most provide password confirmation", 400)

        elif password != confirmation:
            return apology("passwords must match", 400)

        # Insert new user into database
        db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", newUsername, generate_password_hash(password))

        rows = db.execute("SELECT * FROM users WHERE username = ?", newUsername)

        # Log user in and remember that this user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect to login form
        return redirect("/")

    # User reached route via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    owns = own_shares()
    if request.method == "GET":
        return render_template("sell.html", owns = owns.keys())

    symbol = request.form.get("symbol")
    shares = int(request.form.get("shares"))

    # check whether there are sufficient shares to sell
    if owns[symbol] < shares:
        return render_template("sell.html", invalid=True, symbol=symbol, owns=owns.keys())
    # Execute sell transaction: look up sell price, and add fund to cash,
    result = lookup(symbol)
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
    price = result["price"]
    remain = cash + price * shares
    db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, user_id)
    # Log the transaction into orders
    totalPrice = shares * price
    db.execute("INSERT INTO purchases (user_id, shareSymbol, numShares, pricePerShare, timestamp, totalPrice) VALUES (?, ?, ?, ?, ?, ?)",
                user_id, symbol, -shares, price, time_now(), totalPrice)

    return redirect("/")


def time_now():
    """HELPER: get current UTC date and time"""
    now_utc = datetime.now(timezone.utc)
    return str(now_utc.date()) + ' @time ' + now_utc.time().strftime("%H:%M:%S")


def own_shares():
    """Helper function: Which stocks the user owns, and numbers of shares owned. Return: dictionary {symbol: qty}"""
    user_id = session["user_id"]
    owns = {}
    query = db.execute("SELECT shareSymbol, numShares FROM purchases WHERE user_id = ?", user_id)
    for q in query:
        symbol, shares = q["shareSymbol"], q["numShares"]
        owns[symbol] = owns.setdefault(symbol, 0) + shares
    # filter zero-share stocks
    owns = {k: v for k, v in owns.items() if v != 0}
    return owns
import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, format_datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd
app.jinja_env.filters['formatdatetime'] = format_datetime

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
    # select stocks info gruped
    infos = db.execute(
        "SELECT min(symbol) as symbol, sum(quanty) as quanty FROM history where id_user = ? GROUP BY SYMBOL HAVING sum(quanty) > 0", session["user_id"])
    # take info of user cash

    data = db.execute("SELECT cash FROM users WHERE id = ?",
                      session["user_id"])
    cash = data[0]["cash"]
    # in empty list append as dict info by template symbol, quanty, actual price
    datas = []
    total_price = 0
    for info in infos:
        actual_price = lookup(info["symbol"])
        total_price += round(float(info["quanty"]) * actual_price["price"], 2)
        datas.append(
            {'symbol': info["symbol"], 'quanty': info["quanty"], "price": actual_price["price"]})
    info = {'cash': cash, 'stocks': total_price}
    return render_template("index.html", datas=datas, info=info)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        """Get stock quote."""
        symbol = request.form.get("symbol")

        # if front is manipulated and shares input isn't a number return apology
        try:
            shares = float(request.form.get("shares"))
        except:
            return apology("Please input a positive number", 403)
        symbol = lookup(symbol)

        # when are errors
        if symbol == "":
            return apology("Please write a symbol", 403)
        elif symbol == None:
            return apology("Please write a valid symbol", 403)
        elif shares <= 0:
            return apology("Please input a positive number", 403)
        # correct info
        else:
            cost = shares * symbol["price"]
            data = db.execute(
                "SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash = data[0]["cash"]
            if cash >= cost:
                db.execute("INSERT INTO history (symbol, quanty , price , action , id_user) VALUES ( ? , ? , ? , ? , ?)",
                           symbol["symbol"], shares, symbol["price"], "buy", session["user_id"])

                db.execute("UPDATE users set cash = ? where id = ?",
                           (cash - cost), session["user_id"])
                return redirect("/")
            else:
                return apology("Transaccion Cost greater than cash", 400)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    datas = db.execute(
        "SELECT * FROM HISTORY WHERE id_user = ?", session["user_id"])
    return render_template("history.html", datas=datas)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

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
    if request.method == "POST":
        """Get stock quote."""
        # when symbol is blanck
        symbol = request.form.get("symbol")
        info = lookup(symbol)
        if symbol == "":
            return apology("Please write a symbol", 403)
        elif info == None:
            return apology("Please write a valid symbol", 403)
        else:
            return render_template("quoted.html", info=info)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # When username wasn't submitted.
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # When password wasn't submitted.
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # When confirmation pass wasn't submitted.
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 403)

        # When password and confirmation don't match
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("must provide equals passwords", 403)

        # Query database for username exists
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # When Query row return value then this username exists
        if len(rows) != 0:
            return apology("user already exists, please provide another username", 403)

        # get hashed password and user for insert en DB
        password_hashed = generate_password_hash(request.form.get("password"))
        username = request.form.get("username")

        db.execute("INSERT INTO users (username , hash) VALUES (? , ?)",
                   username, password_hashed)

        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    datas = db.execute(
        "SELECT symbol FROM history  WHERE id_user = ? group by symbol having sum(quanty) > 0", session["user_id"])
    if request.method == "POST":
        """Get stock quote."""
        symbol = request.form.get("symbol")


        # if front is manipulated and shares input isn't a number return apology
        try:
            shares = float(request.form.get("shares"))
        except:
            return apology("Please input a positive number", 403)

        # when are errors
        if symbol == "":
            return apology("Please select a symbol", 403)
        elif symbol == None:
            return apology("Please select a valid symbol", 403)
        elif shares <= 0:
            return apology("Please input a positive number", 403)
        # correct info
        else:
            symbol = lookup(symbol)

            info = db.execute(
                "SELECT sum(quanty) as quanty FROM history where id_user = ? and symbol = ?", session["user_id"], symbol["symbol"])
            user_info = db.execute(
                "SELECT cash from users where id = ?", session["user_id"])

            cash = round(float(user_info[0]['cash']), 2)
            quanty = round(float(info[0]['quanty']), 2)

            if quanty >= shares:
                cash += round(float(symbol['price']*shares), 2)
                db.execute("INSERT INTO history (symbol, quanty , price , action , id_user) VALUES ( ? , ? , ? , ? , ?)",
                           symbol["symbol"], shares*-1, symbol["price"], "sell", session["user_id"])

                db.execute("UPDATE users set cash = ? where id = ?",
                           cash, session["user_id"])
            else:
                return apology("Quantity are greater than shares", 403)

            return redirect("/")

    else:
        return render_template("sell.html", datas=datas)


@app.route("/users", methods=["GET", "POST"])
@login_required
def users():
    if request.method == "POST":
        cash = request.form.get("cash")
        try:
            cash = float(cash)
        except:
            return apology("Please input a positive number", 403)
        if cash == "":
            return apology("Please provide a quantity", 403)
        elif cash <= 0:
            return apology("Please input a positive number", 403)
        else:
            data = db.execute(
                "SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash += data[0]["cash"]
            db.execute("UPDATE users SET cash = ? where id = ?",
                       cash, session["user_id"])
            return redirect("/")
    else:
        return render_template("users.html")

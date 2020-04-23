import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
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
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # Handle information from POST
    if request.method == "POST":

        # Validity checker for symbol and shares
        if not request.form.get("symbol"):
            return apology("missing symbol")
        elif int(request.form.get("shares")) <= 0:
            return apology("not positive integer")
        else:
            results = lookup(request.form.get("symbol"))
            if results is None:
                return apology("symbol not found")

        # Assign quanity of shares to be bought and user's cash amount to variables
        quantity = int(request.form.get("shares"))
        cash = db.execute("SELECT cash FROM users WHERE id = :id",
                          id=session["user_id"])[0]["cash"]

        # Not enough cash, render apology
        if quantity * results["price"] > cash:
            return apology("not enough cash")

        # Buy shares and update 'users' and 'transactions' tables
        else:
            cash -= quantity * results["price"]
            db.execute("INSERT INTO transactions (user_id, symbol, quantity, price, time) VALUES (:id, :symbol, :quantity, :price, :time)",
                       id=session["user_id"],
                       symbol=results["symbol"],
                       quantity=quantity,
                       price=usd(results["price"]),
                       time=datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
            db.execute("UPDATE users SET cash=:cash WHERE id=:id",
                       cash=cash,
                       id=session["user_id"])
            return redirect("/")

    # If visited from GET, render buy webpage
    else:
        return render_template("buy.html")


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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

    # Handle information from POST
    if request.method == "POST":

        # Check if field is empty
        if not request.form.get("symbol"):
            return apology("missing symbol")

        # Store lookup reults in dict called result
        result = lookup(request.form.get("symbol"))

        # Lookup fail, render apology
        if result is None:
            return apology("symbol not found")

        # Lookup successful, show webpage with details
        else:
            return render_template("quoted.html",
                                   name=result["name"],
                                   price=usd(result["price"]),
                                   symbol=result["symbol"])

    # If visited by GET, show quote webpage
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # For information sent via POST
    if request.method == "POST":

        # Validity check for username and password
        if not request.form.get("username"):
            return apology("must provide username")
        elif not request.form.get("password"):
            return apology("must provide password")
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password must match confirmation")

        # Insert user details into database
        registered = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                                username=request.form.get("username"),
                                hash=generate_password_hash(request.form.get("password")))

        # Insertion fail, render apology
        if registered is None:
            return apology("unable to register")

        # Insertion successful, log user in and redirect to index page
        else:
            flash("Registered!")
            session["user_id"] = db.execute("SELECT id FROM users WHERE username = :username",
                              username=request.form.get("username"))[0]["id"]
            return redirect("/")

    # send user to registration page if visited via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

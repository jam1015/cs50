# this is not my original work: it is the solution found at https://raw.githubusercontent.com/Mayconpm/CS50x_2021/master/pset9/finance/application.py
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask.helpers import get_flashed_messages
from flask_session import Session
from helpers import apology, login_required, lookup, usd
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import os

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
	return apology("TODO")


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
		rows = db.execute("SELECT * FROM users WHERE username = ?",
		                  request.form.get("username"))

		# Ensure username exists and password is correct
		if len(rows) != 1 or not check_password_hash(
		    rows[0]["hash"], request.form.get("password")):
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
	if request.method == "POST":
		quote = lookup(request.form.get("symbol"))
		# Ensure the simbol was submitted
		if quote is None:
			return apology("must provide valid symbol", 400)
		else:
			return render_template(
			    "quoted.html",
			    name=quote["name"],
			    symbol=quote["symbol"],
			    price=quote["price"],
			)
	# User reached route via GET (as by clicking a link or via redirect)
	else:
		return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
	"""Register user"""
	if request.method == "POST":

		username = request.form.get("username")
		password = request.form.get("password")
		confirmation = request.form.get("confirmation")

		rows = db.execute("SELECT * FROM users WHERE username = ?", username)

		# Ensure the username was submitted
		if not username:
			return apology("must provide username", 400)
		# Ensure the username doesn't exists
		elif len(rows) != 0:
			return apology("username already exists", 400)

		# Ensure password was submitted
		elif not password:
			return apology("must provide password", 400)

		# Ensure confirmation password was submitted
		elif not request.form.get("confirmation"):
			return apology("must provide a confirmation password", 400)

		# Ensure passwords match
		elif not password == confirmation:
			return apology("passwords must match", 400)

		else:
			# Generate the hash of the password
			hash = generate_password_hash(password,
			                              method="pbkdf2:sha256",
			                              salt_length=8)
			# Insert the new user
			db.execute(
			    "INSERT INTO users (username, hash) VALUES (?, ?) ",
			    username,
			    hash,
			)
			# Redirect user to home page
			return redirect("/")

	# User reached route via GET (as by clicking a link or via redirect)
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
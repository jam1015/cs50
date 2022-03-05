import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime, timezone

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
#transactions: transaction id (unique); tx_type, user_id; time; ticker; num shares; price per share;
db.execute(
    "CREATE TABLE IF NOT EXISTS transactions (tx_id INTEGER NOT NULL, id INTEGER NOT NULL, symbol TEXT NOT NULL, price REAL NOT NULL, shares INTEGER  NOT NULL ,time DATETIME NOT NULL, PRIMARY KEY(tx_id))"
)
print("made transactions table")

# Make sure API key is set
if not os.environ.get("API_KEY"):
	raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
	"""Show portfolio of stocks"""
	hist_dict = db.execute("SELECT * FROM transactions where id=? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])
	cash = db.execute("SELECT cash FROM users where id=?", session["user_id"])
	breakpoint()

#	quote_dict = lookup(symbol)
#	price=usd(quote_dict["price"]
#	symbol=quote_dict["symbol"]
#	name=quote_dict["name"]
#
#		if quote_dict is None:
#			return redirect("/quote")

	# want which  stocks, numbers of shares, current price, total value
	# cash
	# net worth

	return render_template("index.html")


@app.route("/history")
@login_required
def history():
	hist_dict = db.execute("SELECT * FROM transactions where id=?", session["user_id"] )
	for row in hist_dict:
		if row['price'] < 0:
			row['price'] = -row['price']
			row['transaction_type'] = 'buy'
		else:
			row['transaction_type'] = 'sell'
			row['shares']= -row['shares']
	return render_template("history.html", transactions = hist_dict)

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


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
	request_time = datetime.now(timezone.utc)
	"""Buy shares of stock"""
	if request.method == "GET":
		return render_template("buy.html")
	if request.method == "POST":
		symbol = request.form.get("symbol")
		if not symbol:
			return apology("must input a ticker symbol", 403)


# getting the number of shares input
		shares = int(request.form.get("shares"))
		negative_shares = shares < 1
		shares_int_type = isinstance(shares, int)

		if negative_shares or (not shares_int_type and not shares_int_value):
			return apology("need positive integer number of shares")
		quote_dict = lookup(symbol)
		share_price = quote_dict["price"]

		total_price = shares * share_price

		print("user id" + str(session["user_id"]))

		cash_dict = db.execute("SELECT cash from USERS WHERE id=?",
		                       session["user_id"])

		cash = cash_dict[0]["cash"]

		if total_price > cash:
			return apology("you do not have enough money!!!!")

		db.execute(
		    "INSERT INTO  transactions  (id, price, symbol, shares, time) VALUES( ?, ?, ?, ?, ?)",
		    session["user_id"], -share_price, symbol, shares, request_time)

		db.execute('UPDATE users SET cash=? WHERE id=?', cash - total_price,
		           session["user_id"])

		return redirect("/")
		#return render_template("buy_display.html",
		#                       price=usd(quote_dict["price"]),
		#                       symbol=quote_dict["symbol"],
		#                       name=quote_dict["name"],
		#					   shares=shares)


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
	if request.method == "GET":
		return render_template("quote_entry.html")
	if request.method == "POST":
		symbol = request.form.get("symbol")

		if not symbol:
			return redirect("/quote")

		quote_dict = lookup(symbol)

		if quote_dict is None:
			return redirect("/quote")

		return render_template("quote_display.html",
		                       price=usd(quote_dict["price"]),
		                       symbol=quote_dict["symbol"],
		                       name=quote_dict["name"])


@app.route("/register", methods=["GET", "POST"])
def register():
	"""Register user"""
	if request.method == "POST":

		if not request.form.get("username"):
			return apology("must provide username", 403)

		# Ensure password was submitted
		elif not request.form.get("password"):
			return apology("must provide password", 403)

		un = request.form.get("username")
		pw = request.form.get("password")
		confirmation = request.form.get("confirmation")

		if pw != confirmation:
			return apology("passwords don't match", 403)
		hash = generate_password_hash(pw)

		print(hash)

		rows = db.execute("SELECT * FROM users WHERE username = ?", un)

		if len(rows) != 0:
			return apology("username already exists", 403)

		db.execute("INSERT INTO  users  (username, hash) VALUES(?,?)", un,
		           hash)

		# Ensure username exists and password is correct
		rows = db.execute("SELECT * FROM users WHERE username = ?", un)

		if len(rows) != 1 or not check_password_hash(rows[0]["hash"], pw):
			return apology("invalid username and/or password", 403)

		# Remember which user has logged in
		session["user_id"] = rows[0]["id"]

		# Redirect user to home page
		return redirect("/")

		# Redirect user to home page
		return redirect("/login")
	else:
		return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
	"""Sell shares of stock"""
	if request.method == "GET":
		shares_wanted = db.execute(
		    "SELECT symbol, SUM(shares) as sum_shares FROM transactions WHERE id = ?  GROUP BY symbol HAVING SUM(shares) > 1",
		    session["user_id"])

		return render_template("sell.html", shares=shares_wanted)

	if request.method == "POST":
		request_time = datetime.now(timezone.utc)
		# getting the symbol
		symbol = request.form.get("symbol")
		if not symbol:
			return apology("must input a ticker symbol", 403)


		# getting the number of shares input
		shares = int(request.form.get("shares"))
		negative_shares = shares < 1
		shares_int_type = isinstance(shares, int)
		shares_int_value = False # if it is not of int type, is it a float with integer value?
		if not shares_int_type:
			shares_int_value = shares.is_integer()

		if negative_shares or (not shares_int_type and not shares_int_value):
			return apology("need positive integer number of shares")
		quote_dict = lookup(symbol)
		share_price = quote_dict["price"]

		total_price = shares * share_price

		shares_wanted = db.execute(
		    "SELECT symbol, SUM(shares) as sum_shares FROM transactions WHERE id = ?  GROUP BY symbol HAVING SUM(shares) > 1",
		    session["user_id"])

		found_shares = False
		shares_available = 0
		for record in shares_wanted:
			if record["symbol"] == symbol:
				found_shares = True
				record_used = record
				shares_available = record_used["sum_shares"]
				break

		if not found_shares or shares_available == 0:
			return apology("you don't have that stock")

		if shares_available < shares:
			return apology(
			    "you don't have enough of that stock to sell that many shares")

		db.execute(
		    "INSERT INTO  transactions  (id, price, symbol, shares, time) VALUES( ?, ?, ?, ?, ?)",
		    session["user_id"], share_price, symbol, -shares, request_time)

		db.execute('UPDATE users SET cash= cash + ? WHERE id=?', total_price,
		           session["user_id"])

		return redirect("/")
		return apology("TODO")


def errorhandler(e):
	"""Handle error"""
	if not isinstance(e, HTTPException):
		e = InternalServerError()
	return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
	app.errorhandler(code)(errorhandler)

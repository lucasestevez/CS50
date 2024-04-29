import os
from flask_session import Session
from tempfile import mkdtemp
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from modules import registers

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        day = int(request.form.get("day"))
        month = int(request.form.get("month"))

        if day == 31 and month == 2 or month == 4 or month == 6 or month == 9 or month == 11:
            rows = registers.get_birthdays_registers()
            flash("this month don't have 31 days", 'danger')
            return render_template("index.html", birthdays=rows)
        else:
            rows = registers.get_birthdays_registers()
            for row in rows:
                if row["name"] == name and row["day"] == day and row["month"] == month:
                    flash("This person already exists in the database ", 'danger')
                    return render_template("index.html", birthdays=rows)
            registers.register_new_birthday(name, month, day)
            flash("Registered!", 'success')

        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        rows = registers.get_birthdays_registers()
        return render_template("index.html", birthdays=rows)


# @app.route("/update", methods=["GET", "PUT"])
# def update():

#     if request.method == "PUT":

#         new_name = request.form.get("new_name")
#         new_day = int(request.form.get("new_day"))
#         new_month = int(request.form.get("new_month"))

#         print(f"{session['name']}, {session['day']}, {session['month']}")
#         print(f"{new_name}, {new_day}, {new_month}")

#         rows = registers.get_birthdays_registers()
#         return render_template("index.html", birthdays=rows)

#     else:

#         return render_template("update.html")

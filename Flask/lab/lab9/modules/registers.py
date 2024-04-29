from cs50 import SQL

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


def get_birthdays_registers():
    rows = db.execute("SELECT * FROM birthdays")
    return rows

def register_new_birthday(name, month, day):
    db.execute(
                "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
    
from sys import argv, exit
from cs50 import SQL

# Exit program if number of arguments incorrect
if len(argv) != 2:
    exit("Incorrect number of arguments")

# Open db file using sqlite
db = SQL("sqlite:///students.db")

# Get list of students in house, sorted by last and first name
students = db.execute("SELECT first, middle, last, birth FROM students WHERE house==? ORDER BY last ASC, first ASC", argv[1])

# Print list of students
for student in students:
    if student["middle"] == None:
        name = f"{student['first']} {student['last']}"
    else:
        name = f"{student['first']} {student['middle']} {student['last']}"

    print(f'{name}, born {student["birth"]}')
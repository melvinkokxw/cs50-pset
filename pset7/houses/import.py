from sys import argv, exit
from cs50 import SQL
import csv

# Exit program if number of arguments incorrect
if len(argv) != 2:
    exit("Incorrect number of arguments")

# Open provided csv file and import as list of dictionaries
with open(argv[1], "r") as characters:
    reader = csv.DictReader(characters)
    students = list(reader)

# Split names into first, middle and last names
for student in students:
    student["name"] = student["name"].split()
    if len(student["name"]) == 2:
        student["first"] = student["name"][0]
        student["middle"] = None
        student["last"] = student["name"][1]
    else:
        student["first"] = student["name"][0]
        student["middle"] = student["name"][1]
        student["last"] = student["name"][2]
    del student["name"]

# Open db file using sqlite
db = SQL("sqlite:///students.db")

# Insert each student into db file
for student in students:
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
               student["first"], student["middle"], student["last"], student["house"], student["birth"])
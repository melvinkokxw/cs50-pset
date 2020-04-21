from sys import argv, exit
import csv
import re
from collections import OrderedDict

# Check for correct number of arguments
if len(argv) != 3:
    print("Usage: python dna.py [database] [profile]")
    exit()

# Open database file and create list of people as dictionaries
with open(argv[1], newline='') as database:
    people = csv.DictReader(database)
    header = people.fieldnames
    people = list(people)
    for person in people:
        person = dict(person)

# Open dna sequence to be matched and save to string
with open(argv[2]) as dnafile:
    dnaprofile = dnafile.read()

# Create profile for dna sequence to be matched
profile = OrderedDict.fromkeys(header)
profile.popitem(last=False)


# Recursive function to find longest match for regex
def findLongest(expression, string, longest):
    match = re.search(expression, string)

    # If no more matches, return current longest value
    if not match:
        return longest

    # If match exists and longer than current longest, update longest
    matchlength = match.end() - match.start()
    if matchlength > longest:
        longest = matchlength

    # Recursively call function on string, starting after end of match
    longest = findLongest(expression, string[match.end():], longest)
    return longest


# Update profile with number of sequences matched
for k, v in profile.items():
    longest = 0
    longest = findLongest(rf"({k})+", dnaprofile, longest)
    longest /= len(k)
    profile[k] = int(longest)


# Check if profile matches anyone in list
for person in people:
    match = True
    for k, v in profile.items():
        if v != int(person[k]):
            match = False
    if match:
        print(person["name"])
        exit()
print("No match")

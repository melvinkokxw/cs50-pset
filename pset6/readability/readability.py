# Initialise variables
letters = 0
words = 1
sentences = 0

# Get text input
text = input("Text: ")

# Iterate over text and find markers for letters, words and sentences
for i in text:
    if i.isalpha():
        letters += 1

    if i == " ":
        words += 1

    if i in {".", "!", "?"}:
        sentences += 1

# Get average letters and sentences per 100 words
averageLetters = letters / words * 100
averageSentences = sentences / words * 100

# Get Coleman-Liau index
index = round(0.0588 * averageLetters - 0.296 * averageSentences - 15.8)

# Print results
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
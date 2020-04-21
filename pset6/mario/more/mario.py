# Main function
def main():
    height = getHeight()
    printWall(height)


# Gets user input of interger betweeen 1-8
def getHeight():
    while (True):
        try:
            height = int(input("Height: "))
        except ValueError:
            continue
        else:
            if height >= 1 and height <= 8:
                break
            else:
                continue

    return height


# Prints wall as specified
def printWall(height):
    for i in range(1, height + 1):
        print(" " * (height - i), end="")
        print("#" * i, end="")
        print("  ", end="")
        print("#" * i, end="")
        print()


# Calls main function
main()
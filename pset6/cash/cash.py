# Main function
def main():
    # Get amount owed
    amount = getAmount()

    # List of types of coins
    coinCount = 0
    coinTypes = [25, 10, 5, 1]

    # Iterate through coin type list
    # While amount greater than or equal to value of coin, reduce amount by value of coin
    for type in coinTypes:
        while amount >= type:
            amount -= type
            coinCount += 1
    print(coinCount)


# Get float greater than 0
def getAmount():
    while True:
        try:
            amount = float(input("Change owed: "))
        except ValueError:
            continue
        else:
            if amount < 0:
                continue
            else:
                break
    return int(amount * 100)


main()
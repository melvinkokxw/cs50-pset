# Credit Card Authenticator

Credit card authenticator is a program written in C to validate a credit card number. If the card is valid, the program checks if it is from Amex, MasterCard or Visa.

## Method

To check if the cards are valid and what type they are, the following methods were used:

* The method used to validate the card number is the [Luhn algorithm](https://en.wikipedia.org/wiki/Luhn_algorithm).

* All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55 and all Visa numbers start with 4

## Usage

Compile the program

```bash
make credit
```

Run using

```bash
./credit
```

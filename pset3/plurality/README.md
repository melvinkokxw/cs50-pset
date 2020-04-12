# Plurality

This program runs a [plurality election](https://en.wikipedia.org/wiki/Plurality_voting).

A plurality election is a simple election where each voter votes for one candidate and the candidate with the highest number of votes wins.

The program takes in up to 9 candidates via command-line arguments. The total number of voters will be requested and each voter will have to input a candidate name. The `vote` function will be used to check the validity of the vote and add the vote to the candidate accordingly.

## Usage

```
./plurality [candidate ...]
```

```
./plurality Alice Bob Charlie
Number of voters: 5
Vote: Alice
Vote: Charlie
Vote: Bob
Vote: Bob
Vote: Alice
Alice
Bob
```

```
./plurality Alice Bob
Number of voters: 3
Vote: Alice
Vote: Charlie
Invalid vote.
Vote: Alice
Alice
```

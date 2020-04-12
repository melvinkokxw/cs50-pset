# Runoff

This program runs an [instant runoff election](https://en.wikipedia.org/wiki/Instant-runoff_voting).

An instant runoff election requires every voter to rank candidates in order of preference. If a candidate has more than half the vote based on first choices, that candidate is declared the winner. Otherwise, the candidate with the fewest votes is eliminated and the voters who had that candidate as their first choice have their vote shifted to the next candidate in order of their preference.

This process continues until a candidate has the majority vote.

The program takes in up to 9 candidates via command-line arguments. The total number of voters will be requested and each voter will have indate their preferences for the candidates. The `vote` function will be used to check the validity of the vote and add the voter's preferences to a two-dimensional array `preferences`, where `preferences[i][j]` stores the candidate index for voter `i`'s `j`th preference. If a ballot is invalid, the program exits.

A loop is then used to repeat the runoff process until a winner is determined.

The runoff process starts with the `tabulate` function, used to total the number of votes for candidates who have yet to be eliminated. The `print_winner` function then determines if there is a winner and prints the winner's name if there is one. If there is no winner, the `find_min` function is used to determine the fewest votes in the election. The `is_tie` function checks if a tie will be caused due to all remaining candidates having the same number of votes. If no there is no tie determined, the `eliminate` function then eliminates all candidates with the fewest votes as previously determined using the `find_min` function, and the runoff process starts again.

## Usage

```
./runoff [candidate ...]
```

```bash
./runoff Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Alice
```

## Lessons

No new techniques were used in this program. However, I learned to break down the tasks from a program into many smaller functions, making the problem easier to solve and debug.

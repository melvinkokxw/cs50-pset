# Tideman

This program runs an [Tideman election](https://en.wikipedia.org/wiki/Ranked_pairs).

As the Tideman election process is too lengthy, the election process explanation will be omitted from this readme.

## Usage

```
./tideman [candidate ...]
```

```bash
./tideman Alice Bob Charlie
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

Charlie
```

## Lessons

Other than using multiple functions to break down the problem making it easier to solve and debug, algorithms such as merge sort and depth-first search (DFS) were also needed to create the program.

When sorting the pairs, I used merge sort as it has the highest efficiency among the [sorting algorithms](/Notes/week3.md#sorting) we learned in week 3. Merge sort requires two functions - the main `merge_sort` function and a `merge` function.

While the algorithm was not too challenging to create in code, it was difficult to manage the value used to compare the pairs, as the value used to compare between pairs was not stored in the pairs variable itself. This resulted in lengthy, confusing variable names (e.g. `preferences[pairs_arr[pointer2].winner][pairs_arr[pointer2].loser]`). I am still looking for a solution!

When locking the pairs in to create the adjacency matrix, to ensure no cycles are present, I used a DFS approach to check for cycles each time an edge is added. If a cycle is present after an edge is added, this indicates that adding the edge causes a cycle and the edge is removed.

Two arrays are used to keep track of visited vertices - `visited`, which keeps track of all vertices visited and `rec_visited`, which keeps track of the vertices visited on the current recursive "visit".

Checking for a cycle uses two functions. The first `visit` function, which adds a vertex to the `visited` array, then recursively calls the `visit` function on connected vertices. The main `find_cycle` function calls the `visit` function on each vertex if the vertex has not been visited.

The main challenge with implementing the DFS search was that the program was initially causing false positives. This was because the `rec_visited` array was not implemented originally, so the algorithm ignored the direction of the edges.

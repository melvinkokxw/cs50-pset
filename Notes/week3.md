# Week 3: Algorithms

* [Structs](#structs)
* [Big O](#big-o)
* [Recursion](#recursion)
* [Searching](#searching)
  * [Linear search](#linear-search)
  * [Binary search](#binary-search)
* [Sorting](#sorting)
  * [Bubble sort](#bubble-sort)
  * [Selection sort](#selection-sort)
  * [Insertion sort](#insertion-sort)
  * [Merge sort](#merge-sort)

## Structs

We can define our own custom data types in C called structs using `typedef struct`. The following piece of code is an example of using `typedef struct` to declare a new data type:

```C
typedef struct
{
    string name;
    string number;
}
person;
```

Here, a data type with a struct called `person` has been created, which will have a string called `name` and a string called `number`. The new data type can be used like this:

```C
person person1;
person1.name = "Melvin";
person1.number = "91234567";
```

Here, a variable `person1` of data type `person` has been declared, and the properties `name` and `number` have been initialized using `.`.

Personal note: This seems similar to objects in other languages.

## Big O

Big O notation is the formal way to describe an algorithm's running time. If we say an algorithm has running time of O(*n*) , that means the algorithm takes approximately *n* steps to run, or “on the order of *n*”.

Since big O notation represents an upper bound of the running time, even an algorithm that takes n/2 steps has O(*n*) because as *n* gets bigger and bigger, only the largest term, *n*, matters..

Some common running times are:
* O(*n*<sup>2</sup>)
* O(*n* log *n*)
* O(*n*)
* O(log *n*)
* O(1)

The list is non-exhaustive.

### Big Ω

Another common notation used is Ω, big Omega notation. Big Ω represents the lower bound of number of steps for an algorithm. For example, in a [linear search](#linear-search), it has O(*n*) but has Ω(1) since it is possible that we obtain the search result from the first value we check.

### Big θ

If an algorithm's big O notation and big Ω notation is the same, then we can use big θ, big theta notation to describe both running times. For example, [merge sort](#merge-sort) has Θ(*n* log *n*) since it has O(*n*) and Ω(*n*).

## Recursion

Recursion occurs where a function or algorithm refers to itself. The basic idea for recursion is:
* Break up the big problem - perform an action + recursively call the function to perform its function on a slightly smaller problem set
* Define what conditions to stop calling the function recursively

Using the example from [pset2](../pset2/), mario, instead of using a nested loop to print a pyramid as follows:

```C
// Draw pyramid of height h
for (int i = 1; i <= h; i++)
{
    for (int j = 1; j <= i; j++)
    {
        printf("#");
    }
    printf("\n");
}
```

We can do the following

```C
// If nothing to draw, end program here
if (h == 0)
{
    return;
}

// Draw pyramid of height h – 1
draw(h – 1);

// Draw one more row of width h
for (int i = 0; i < h; i++)
{
    printf("#");
}

printf("\n");
```

The program above breaks the problem of drawing a pyramid into parts:
* Recursively call itself to draw a pyramid one unit smaller
* Draw the bottom row of hashes
* Stop calling the function when at the base case

## Searching

Searching is often performed to search for a value in a collection of values, such as in an array. This collection of values can be sorted or unsorted. Since the computer cannot look at all the values at once and immediately pick a number out, it needs an algorithm to go through the data and search for a value.

Two common searching algorithms are [linear search](#linear-search) and [binary search](#binary-search).
As a summary of each sorting algorithm's big O and big Ω notation:

Searching algorithm | O | Ω
-|-|-
Linear search | *n* | 1
Binary search | log *n* | 1

### Linear search

This approach searches through an array of values one at a time, linearly, e.g. front to back.

An example of such a implementation where we search for a value *m* in an array of size *n* is:

```C
// Search for value m in array
for (i = 0 ; i < n ; i++)
{
  // If value has been found, return true
  if (array[i] == m)
  {
    return true;
  }
}

//If value has not been found, return false
return false;
```

Since linear search can take up to *n* steps to search through the array (item is in the last slot or not even present), linear search has O(*n*). However, since the first value in the array may be the correct result, it has Ω(1).

### Binary search

Binary search requires the array to be sorted beforehand. Using binary search, we repeatedly divide our problem into two with each step and [recursively](#recursion) call the binary search on the relevant half to find the value.

An example of such a implementation where we search for a value *m* in a sorted array of size *n* is:

```C
// Use binary search to find value m in array
int binary_search(int array, int array_start, int array_end)
{
  // If value cannot be found, return false
  if (array_end < array_start)
  {
    return false;
  }

  // Finding value in middle of array
  middle_value = array[(array_end - array_start)/2]

  // If middle value of array is m, return true
  if (middle_value == m)
  {
    return true;
  }
  // If m is smaller than middle value, recursively call binary search on left half of array
  else if (m < middle_value)
  {
    binary_search(array, start, middle_value - 1);
  }
  // If m is larger than middle value, recursively call binary search on right half of array
  else if (m > middle_value)
  {
    binary_search(array, middle_value + 1, end);
  }
}
```

Since binary search can take up to log *n* steps to search through the array (item is in the last slot or not even present), binary search has O(log *n*). However, since the first value we try may be the correct result, it has Ω(1).

log *n* is derived from as follows:

Assume an array of size *n* that is halved repeatedly *m* times until it becomes an array of size 1. The maximum number of steps it takes to perform binary search is then *m*. Since n = 2<sup>*m*</sup>, *m* = log<sub>2</sub> *n*. Hence big O of binary search is log *n*.

## Sorting

Given a list of unsorted numbers, we can use an algorithm to output a list of sorted numbers. In this lecture we consider four types of sorting algorithms, [bubble sort](#bubble-sort), [selection sort](#selection-sort), [insertion sort](#insertion-sort), and [merge sort](#merge-sort).

As a summary of each sorting algorithm's big O and big Ω notation:

Sorting algorithm | O | Ω
-|-|-
Bubble sort | *n*<sup>2</sup> | *n*
Selection sort | *n*<sup>2</sup> | *n*<sup>2</sup>
Insertion sort | *n*<sup>2</sup> | *n*
Merge sort | *n* log *n* | *n* log *n*

### Bubble sort

An intuitive approach to sorting numbers in ascending order would be to start from the first number in an array and look at each number one at a time, swapping it towards the right if it is larger than the number on its right. This approach causes the large values to “bubble” to the right.

An example of sorting an array of size *n* using bubble sort is as follows:

```C
// Create variable to store temporary value for swapping
int temp = 0;

// Repeat n-1 times
for (i = 0 ; i < n - 1 ; i++)
{
  // Repeat from start of array to (n-1)th item
  for (j = 0 ; j < n - 1; i++)
  {
    // If current value is larger than value to right
    if (array[j] > array[j+1])
    {
      // Swap value and value to right
      temp = array[j];
      array[j] = array[j+1];
      array[j+1] = temp;
      temp = 1;
    }
  }
  // If no swaps were made, quit program
  if (temp == 0)
  {
    return 0;
  }
}
```

Since we are comparing the `i'th` and `i+1'th` element, we only need to go up to `i = n - 1`. We can stop after we’ve made *n* – 1 passes, since we know the largest *n* –1 elements will have bubbled to the right.

Bubble sort takes (*n* - 1)\*(*n* - 2) = *n*<sup>2</sup> – 3*n* + 2 steps to complete in the worst case. Hence bubble sort has O(*n*<sup>2</sup>). In the best case scenario where the array is already sorted, the algorithm still has to go through the array once before determining that no swaps were made and hence the array is already sorted. Hence bubble sort has Ω(*n*).

### Selection sort

Another somewhat intuitive, linear approach we can take to sorting an array of numbers is to look for the largest number in the array. We then swap it with the last unsorted value of the array.

Selection sort takes *n* + (*n* - 1) + (*n* - 2) + ... + 1 = n<sup>2</sup>/2 + n/2 steps to complete, regardless of whether the array is already sorted or not. Hence selection sort has O(*n*<sup>2</sup>), Ω(*n*<sup>2</sup>), and θ(*n*<sup>2</sup>)

### Insertion sort

One approach we can use to go through the array linearly instead of going through it repeatedly is insertion sort. Insertion involves looking at each element one by one and inserting it into its correct place in the sorted portion of the array. By starting from one end of the array, we can assume the first element is already sorted (one element is always sorted......). We then move to the next element, inserting before or after the first element accordingly, and now both elements are sorted. Repeat until the entire array is sorted.

In the worst case scenario where the array is sorted in reverse order, insertion sort requires 1 + 2 + 3 + ... + *n* n<sup>2</sup>/2 + n/2 steps. Hence insertion sort has O(*n*<sup>2</sup>). In the best case scenario where the array is already sorted, we just need to go through the array once, so it has Ω(*n*).

### Merge sort

We can also use recursion to sort an array of numbers, by dividing the array in half and calling the merge sort function on each half of the array. When the array size reaches one, the function returns and we can start merging the halves of the arrays we divided.

Since both halves are assumed to be sorted, we compare the first value of each half and add the smaller into a new array. We then repeat for all the remaining values in the arrays until we have merged the two halves together.

This is repeated until the entire array is sorted.

Since merge sort divides the problem in half each time, the dividing is logarithmic with O(log *n*). Merging takes *n* steps with O(*n*). Hence merge sort has O(*n* log *n*). Merge sort has to perform all the steps even if the array is already sorted, so it has Ω(*n* log *n*) and hence θ(*n* log *n*).

## Final notes

An algorithm's efficiency may not be of great importance on a personal scale but when these algorithms are used on large databases, the run time of the program can increase exponentially. A O(*n*) vs O(*n*<sup>2</sup>) program run with 1,000 items can mean 1,000 steps vs 1,000,000.

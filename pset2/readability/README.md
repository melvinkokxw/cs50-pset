# Readability check

This program determines the readability of a piece of text using the [Coleman-Liau index](https://en.wikipedia.org/wiki/Coleman%E2%80%93Liau_index). The Coleman-Liau index of a text is designed to output what (U.S.) grade level is needed to understand the text. The formula is:

`index = 0.0588 * L - 0.296 * S - 15.8`

`L` is the average number of letters per 100 words in the text, and `S` is the average number of sentences per 100 words in the text.

## Assumptions

We assume that the input text is properly structured with the following rules:

> * Letters can be any uppercase or lowercase alphabetic characters, but shouldn’t include any punctuation, digits, or other symbols.
> * Any sequence of characters separated by a space is considered to be a word
>   * A hyphenated word like `"sister-in-law"` should be considered one word, not three).
>   * We'll also assume that a sentence will not start or end with a space, and that a sentence will not have multiple spaces in a row.
> * Any sequence of characters that ends with a `.` or a `!` or a `?` is considered to be a sentence
>   * Although `.` is used in cases where the sentence does not end, sentence boundary detection needs to be a little more intelligent to handle these cases. We ignore this case for now.

## Usage examples

```
$ ./readability
Text: One fish. Two fish. Red fish. Blue fish.
Before Grade 1
```

```
$ ./readability
Text: When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right; when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh.
Grade 8
```

```
$ ./readability
Text: A large class of computational problems involve the determination of properties of graphs, digraphs, integers, arrays of integers, finite families of finite sets, boolean formulas and elements of other countable domains.
Grade 16+
```

# Substitution cipher

This program encrypts a plain text message using the [substitution cipher](https://en.wikipedia.org/wiki/Substitution_cipher).

## Usage

The program takes in 1 command-line argument, an integer, as the cipher key. The plain text message input will be requested after the program is run.

The argument should be a 26 character string with no repeated characters. From the CS50 documentation:

> A key, for example, might be the string `NQXPOMAFTRHLZGECYJIUWSKDVB`. This 26-character key means that `A` (the first letter of the alphabet) should be converted into `N` (the first character of the key), `B` (the second letter of the alphabet) should be converted into `Q` (the second character of the key), and so forth.

## Usage examples

```
$ ./substitution JTREKYAVOGDXPSNCUIZLFBMWHQ
plaintext:  HELLO
ciphertext: VKXXN
```

```
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
plaintext:  hello, world
ciphertext: jrssb, ybwsp
```

## Phonecode in C

Library to find dial-pad words in phone numbers in the spirit of Prechelt's "phonecode" paper

[*An empirical comparison of C, C++, Java, Perl, Python, Rexx, and Tcl for a search/string-processing program*
](http://page.mi.fu-berlin.de/prechelt/Biblio/jccpprtTR.pdf)

This implementation deliberately did not use existing data structure libraries, such as `gnulib` or `glib`

## Use

The function 
```
void find_encodings(
    const char *phone_number,
    const dict_t *dictionary,
    string_collection_t *output_encodings )
```

takes a string `phone_number` of the phone number to be parsed and two data structures allocated by the user.

`dict_t` is the dictionary of available words

```
struct dict_t {
    size_t size;
    char const **strings;
};
```

where `size` is the number of entries in the dictionary and `strings` is a set of `NULL` terminated strings.

`string_collection_t` will be filled with the output and sufficient memory must be allocated by the user.

```
struct string_collection_t {
size_t size;
char **strings;
};
```
where `size` will be the number of found word sequences from the dictionary and `strings` is a set of `NULL`
terminated strings of the found sequences.

### Example scenario

A dictionary containing strings `hello` and `world` run with a phone number
`(435) 569-6753` will return a list with `"hello world"`

## Description

Given the following phone dial-pad convention

|1|2|3|4|5|6|7|8|9|0|
|---|---|---|---|---|---|---|---|---|---|
| |ABC|DEF|GHI|JKL|MNO|PQRS|TUV|WXYZ||

given a telephone number and a list of words, find all the possible encoded sequences of words
from the dictionary.

### Functional constraints

- Phone numbers are provided as strings which may include formatting symbols (e.g. -, spaces, parens)
- Phone number length does not matter and can be any length
- The word dictionary will be provided as a structure with the size and array of strings
- The phone number provided will be a string input to a function
- Output will be a structure with the size and array of strings

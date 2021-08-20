#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "util.h"

unsigned int max(unsigned int x, unsigned int y) {
    if (x > y) {
        return x;
    }
    return y;
}

char *new_substring(const char *string, size_t offset, size_t length) {
    char *substring = malloc(sizeof(char) * (length + 1));
    strncpy(substring, &string[offset], length);
    substring[length] = '\0';
    return substring;
}

char get_encoded_digit(char c) {
    switch (tolower(c)) {
        case 'a':
        case 'b':
        case 'c':
            return '2';
        case 'd':
        case 'e':
        case 'f':
            return '3';

        case 'g':
        case 'h':
        case 'i':
            return '4';

        case 'j':
        case 'k':
        case 'l':
            return '5';

        case 'm':
        case 'n':
        case 'o':
            return '6';

        case 'p':
        case 'q':
        case 'r':
        case 's':
            return '7';

        case 't':
        case 'u':
        case 'v':
            return '8';

        case 'w':
        case 'x':
        case 'y':
        case 'z':
            return '9';
        default:
            return '\0';
    }
}

bool is_valid_dial_pad_number(char i1) {
    return '2' <= i1 && i1 <= '9';
}

char *new_sanitized_phone_number(const char *phone_number) {
    int length = 0;
    char *sanitized_phone_number = strdup(phone_number);

    for (size_t i = 0; i < strlen(phone_number); i++) {
        if (is_valid_dial_pad_number(phone_number[i])) {
            sanitized_phone_number[length] = phone_number[i];
            length++;
        }
    }
    sanitized_phone_number[length] = '\0';

    return sanitized_phone_number;
}

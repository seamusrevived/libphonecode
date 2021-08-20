#include <stdbool.h>

#ifndef LIBPHONECODE_UTIL_H
#define LIBPHONECODE_UTIL_H

unsigned int max(unsigned int x, unsigned int y);

char *new_substring(const char *string, size_t offset, size_t length);

char get_encoded_digit(char c);

bool is_valid_dial_pad_number(char i1);

char *new_sanitized_phone_number(const char *phone_number);

#endif //LIBPHONECODE_UTIL_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "phonecode.h"

const int MAX_OUTPUT_LENGTH = 1028;
const int MAX_STRING_LENGTH = 256;


char **initialize_strings_buffer(int max_output_length, int max_string_length) {
    char **output = (char **) malloc(sizeof(char *) * max_output_length);
    for (int i = 0; i < max_output_length; i++) {
        output[i] = (char *) malloc(sizeof(char) * max_string_length);
        memset(output[i], '\0', max_string_length);
    }
    return output;
}

int main(int argc, char **argv) {

    int n_phone_numbers = 3;
    const char *phone_numbers[] = {"(435) 569-6753", "(967) 534-3556", "222"};

    const char *words[] = {"hello", "world", "a", "b", "ab", "ba", "aba"};
    struct dict_t dict = {
            .size = 7,
            .words = words
    };

    struct phone_encodings_t output = {
            .length = MAX_OUTPUT_LENGTH,
            .encodings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    for (int i = 0; i < n_phone_numbers; i++) {
        printf("Phone Number: %s\n", phone_numbers[i]);
        find_encodings(phone_numbers[i], &dict, &output);
        for (unsigned int j = 0; j < output.length; j++) {
            printf("\t%s\n", output.encodings[j]);
        }
    }

    return 0;
}
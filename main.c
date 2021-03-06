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

void free_strings_buffer(char ** buffer, int max_output_length) {
    for (int i = 0; i < max_output_length; i++) {
        free(buffer[i]);
    }
    free(buffer);
}

int main(int argc, char **argv) {

    int n_phone_numbers = 4;
    const char *phone_numbers[] = {"(435) 569-6753", "(967) 534-3556", "222", "232"};

    const char *words[] = {"Hello", "world", "a", "b", "ab", "ba", "aba"};
    dict_t dict = {
            .size = 7,
            .strings = words
    };

    string_collection_t output = {
            .size = MAX_OUTPUT_LENGTH,
            .strings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    for (int i = 0; i < n_phone_numbers; i++) {
        printf("\nPhone Number: %s\n", phone_numbers[i]);
        find_encodings(phone_numbers[i], &dict, &output);
        printf("%d result(s)\n", output.size);
        for (size_t j = 0; j < output.size; j++) {
            printf("\t%s\n", output.strings[j]);
        }
    }

    free_strings_buffer(output.strings, MAX_OUTPUT_LENGTH);
    return 0;
}
#include <cstdlib>
#include <cstring>
#include "phonecode.h"
#include "string_coll.h"

const int MAX_OUTPUT_LENGTH = 1028;
const int MAX_STRING_LENGTH = 256;

char **initialize_strings_buffer(size_t max_output_length, size_t max_string_length) {
    auto output = (char **) malloc(sizeof(char *) * max_output_length);
    for (auto i = 0; i < max_output_length; i++) {
        output[i] = (char *) malloc(sizeof(char) * max_string_length);
        memset(output[i], '\0', max_string_length);
    }
    return output;
}

string_collection_t *initialize_phone_encodings() {
    auto coll = (string_collection_t*) malloc(sizeof(string_collection_t));
    coll->size = 0;
    coll->strings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH);
    return coll;
}

dict_t * initialize_dictionary(size_t size, const char **words) {
    auto dictionary = (dict_t *) malloc(sizeof(dict_t));
    dictionary->size = size;
    dictionary->strings = words;

    return dictionary;
}

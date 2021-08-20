#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include "phonecode.h"
#include "util.h"


string_collection_t *__get_encodings_for_number_with_dictionary(const char *, const dict_t *);
string_collection_t *__find_words_matching_number_in_dictionary(const char *, const dict_t *);
void __build_encodings_for_sequence(string_collection_t *, const char *, const dict_t *);
bool __number_matches_encoding(const char *, const char *);


void find_encodings(
        const char *phone_number,
        const dict_t *dictionary,
        string_collection_t *output_encodings
) {
    char *sanitized_phone_number = new_sanitized_phone_number(phone_number);

    string_collection_t *found_encodings =
            __get_encodings_for_number_with_dictionary(sanitized_phone_number, dictionary);

    raw_copy_string_collection(output_encodings, found_encodings);
    delete_string_collection(found_encodings);
    free(sanitized_phone_number);
}


string_collection_t *
__get_encodings_for_number_with_dictionary(
        const char *phone_number,
        const dict_t *dictionary
) {
    string_collection_t *result = new_string_collection();

    __build_encodings_for_sequence(result, phone_number, dictionary);

    return result;
}

void
__build_encodings_for_sequence(
        string_collection_t *running_result,
        const char *phone_number,
        const dict_t *dictionary
) {
    size_t phone_number_length = strlen(phone_number);

    if (phone_number_length == 0) {
        return;
    }

    string_collection_t *all_partitioning_results = new_string_collection();

    for (size_t i = 0; i < phone_number_length; i++) {
        char *head_sequence = new_substring(phone_number, 0, i + 1);
        char *tail_sequence = new_substring(phone_number, i + 1, phone_number_length - i - 1);

        string_collection_t *partitioning_results = new_string_collection();
        copy_string_collection(partitioning_results, running_result);

        string_collection_t *found_words = __find_words_matching_number_in_dictionary(head_sequence, dictionary);
        if (found_words->size > 0) {
            cross_merge_strings(partitioning_results, found_words);
            __build_encodings_for_sequence(partitioning_results, tail_sequence, dictionary);
            concat_string_collections(all_partitioning_results, partitioning_results);
        }

        free(head_sequence);
        free(tail_sequence);
    }

    copy_string_collection(running_result, all_partitioning_results);
}

string_collection_t *
__find_words_matching_number_in_dictionary(
        const char *phone_number_sequence,
        const dict_t *dictionary
) {
    string_collection_t *found_words = new_string_collection();
    for (unsigned int j = 0; j < dictionary->size; j++) {
        if (__number_matches_encoding(phone_number_sequence, dictionary->strings[j])) {
            add_string_to_string_collection(dictionary->strings[j], found_words);
        }
    }
    return found_words;
}

bool
__number_matches_encoding(
        const char *number,
        const char *word
) {
    char *encoding = strdup(word);

    for (size_t i = 0; i < strlen(word); i++) {
        encoding[i] = get_encoded_digit(word[i]);
    }

    return strcmp(number, encoding) == 0;
}
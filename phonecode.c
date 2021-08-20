#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include "phonecode.h"


char get_encoded_digit(char c) {
    switch (c) {
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

bool number_matches_encoding(const char *number, const char *word) {
    char *encoding = strdup(word);

    for (size_t i = 0; i < strlen(word); i++) {
        encoding[i] = get_encoded_digit(word[i]);
    }

    return strcmp(number, encoding) == 0;
}

struct phone_encodings_t *
find_words_matching_number_in_dictionary(const char *phone_number_sequence, const struct dict_t *dictionary) {
    struct phone_encodings_t *found_words = new_phone_encodings();
    for (unsigned int j = 0; j < dictionary->size; j++) {
        if (number_matches_encoding(phone_number_sequence, dictionary->words[j])) {
            add_word_to_encodings(dictionary->words[j], found_words);
        }
    }
    return found_words;
}

char *create_substring(const char *string, int offset, unsigned int length) {
    char *substring = malloc(sizeof(char) * (length + 1));
    strncpy(substring, &string[offset], length);
    substring[length] = '\0';
    return substring;
}

void build_encodings_for_sequence(struct phone_encodings_t *running_result, const char *phone_number,
                                  const struct dict_t *dictionary) {
    size_t phone_number_length = strlen(phone_number);

    if (phone_number_length == 0) {
        return;
    }

    struct phone_encodings_t *all_partitioning_results = new_phone_encodings();

    for (unsigned int i = 0; i < phone_number_length; i++) {
        char *head_sequence = create_substring(phone_number, 0, i + 1);
        char *tail_sequence = create_substring(phone_number, i + 1, phone_number_length - i - 1);

        struct phone_encodings_t *partitioning_results = new_phone_encodings();
        copy_phone_encodings(partitioning_results, running_result);

        struct phone_encodings_t *found_words = find_words_matching_number_in_dictionary(head_sequence, dictionary);
        if (found_words->length > 0) {
            cross_merge_encodings(partitioning_results, found_words);
            build_encodings_for_sequence(partitioning_results, tail_sequence, dictionary);
            add_encodings(all_partitioning_results, partitioning_results);
        }

        free(head_sequence);
        free(tail_sequence);
    }

    copy_phone_encodings(running_result, all_partitioning_results);
}

struct phone_encodings_t *
get_encodings_for_number_with_dictionary(const char *phone_number, const struct dict_t *dictionary) {
    struct phone_encodings_t *result = new_phone_encodings();

    build_encodings_for_sequence(result, phone_number, dictionary);

    return result;
}

bool is_valid_number(char i1) {
    return '2' <= i1 && i1 <= '9';
}

char *get_sanitized_phone_number(const char *phone_number) {
    int length = 0;
    char *sanitized_phone_number = strdup(phone_number);

    for (size_t i = 0; i < strlen(phone_number); i++) {
        if (is_valid_number(phone_number[i])) {
            sanitized_phone_number[length] = phone_number[i];
            length++;
        }
    }
    sanitized_phone_number[length] = '\0';

    return sanitized_phone_number;
}

void find_encodings(const char *phone_number,
                    const struct dict_t *dictionary,
                    struct phone_encodings_t *output_encodings
) {
    char *sanitized_phone_number = get_sanitized_phone_number(phone_number);

    struct phone_encodings_t *found_mapping =
            get_encodings_for_number_with_dictionary(sanitized_phone_number, dictionary);

    raw_copy_phone_encodings(output_encodings, found_mapping);
    delete_phone_encodings(found_mapping);
    free(sanitized_phone_number);
}



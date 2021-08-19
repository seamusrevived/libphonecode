#include <string.h>
#include <malloc.h>
#include "phonecode.h"


int number_matches_encoding(const char *number, const char *word) {
    size_t len = strlen(word);
    char *encoding = malloc(sizeof(char) * (len + 1));
    encoding[len] = '\0';

    for (unsigned int i = 0; i < len; i++) {
        char encoded_digit = '\0';
        switch (word[i]) {
            case 'a':
            case 'b':
                encoded_digit = '2';
                break;
            case 'd':
                encoded_digit = '3';
                break;
        }
        encoding[i] = encoded_digit;
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

void process_subsequence(struct phone_encodings_t *total, const char *phone_number, const struct dict_t *dictionary) {
    if (strlen(phone_number) == 0) {
        return;
    }

    unsigned int phone_number_length = strlen(phone_number);

    for (unsigned int i = 0; i < phone_number_length; i++) {
        unsigned int head_length = i + 1;
        char *phone_subsequence = malloc(sizeof(char) * (head_length + 1));
        strncpy(phone_subsequence, phone_number, head_length);
        phone_subsequence[head_length] = '\0';

        unsigned int tail_length = phone_number_length - i - 1;
        char *tail_sequence = malloc(sizeof(char) * (tail_length + 1));
        strncpy(tail_sequence, &phone_number[i], tail_length);
        tail_sequence[tail_length] = '\0';

        struct phone_encodings_t *found_words = find_words_matching_number_in_dictionary(phone_subsequence, dictionary);
        merge_encodings(total, found_words);
        process_subsequence(total, tail_sequence, dictionary);
    }
}

struct phone_encodings_t *
get_encodings_for_number_with_dictionary(const char *phone_number, const struct dict_t *dictionary) {
    struct phone_encodings_t *total_result = new_phone_encodings();

    process_subsequence(total_result, phone_number, dictionary);

    return total_result;
}

void find_encodings(const char *phone_number,
                    const struct dict_t *dictionary,
                    struct phone_encodings_t *output_encodings
) {
    struct phone_encodings_t *found_mapping = get_encodings_for_number_with_dictionary(phone_number, dictionary);
    copy_phone_encodings(output_encodings, found_mapping);
    delete_phone_encodings(found_mapping);
}



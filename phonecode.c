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
            case 'c':
                encoded_digit = '2';
                break;
            case 'd':
            case 'e':
            case 'f':
                encoded_digit = '3';
                break;
            case 'g':
            case 'h':
            case 'i':
                encoded_digit = '4';
                break;
            case 'j':
            case 'k':
            case 'l':
                encoded_digit = '5';
                break;
            case 'm':
            case 'n':
            case 'o':
                encoded_digit = '6';
                break;
            case 'p':
            case 'q':
            case 'r':
            case 's':
                encoded_digit = '7';
                break;
            case 't':
            case 'u':
            case 'v':
                encoded_digit = '8';
                break;
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                encoded_digit = '9';
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

    struct phone_encodings_t *all_branch_encodings = new_phone_encodings();

    for (unsigned int i = 0; i < phone_number_length; i++) {
        struct phone_encodings_t *this_branch = new_phone_encodings();

        copy_phone_encodings(this_branch, total);

        unsigned int head_length = i + 1;
        char *phone_subsequence = malloc(sizeof(char) * (head_length + 1));
        strncpy(phone_subsequence, phone_number, head_length);
        phone_subsequence[head_length] = '\0';

        unsigned int tail_length = phone_number_length - i - 1;
        char *tail_sequence = malloc(sizeof(char) * (tail_length + 1));
        strncpy(tail_sequence, &phone_number[i+1], tail_length);
        tail_sequence[tail_length] = '\0';

        struct phone_encodings_t *found_words = find_words_matching_number_in_dictionary(phone_subsequence, dictionary);
        if (found_words->length > 0) {
            merge_encodings(this_branch, found_words);
            process_subsequence(this_branch, tail_sequence, dictionary);
            add_encodings(all_branch_encodings, this_branch);
        }

    }
    copy_phone_encodings(total, all_branch_encodings);
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
    raw_copy_phone_encodings(output_encodings, found_mapping);
    delete_phone_encodings(found_mapping);
}



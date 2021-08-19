#include <string.h>
#include <malloc.h>
#include "phonecode.h"

struct dial_pad_letters_t {
    int length;
    char const **letters;
};

struct dial_pad_letters_t *new_dial_pad(int n, const char **letters) {
    struct dial_pad_letters_t *dial_pad = malloc(sizeof(struct dial_pad_letters_t));
    dial_pad->length = n;
    dial_pad->letters = malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++) {
        dial_pad->letters[i] = strdup(letters[i]);
    }
    return dial_pad;
}


const char *find_word_in_dictionary(const char *target_word, const struct dict_t *dictionary) {
    const char *found_word = NULL;
    for (int j = 0; j < dictionary->size; j++) {
        if (strcmp(target_word, dictionary->words[j]) == 0) {
            found_word = dictionary->words[j];
        }
    }
    return found_word;
}

struct phone_encodings_t *
find_encodings_from_set_in_dictionary(const struct dial_pad_letters_t *dial_pad, const struct dict_t *dictionary) {
    struct phone_encodings_t *encoding_results = new_phone_encodings();

    for (int i = 0; i < dial_pad->length; i++) {
        char const *target_word = dial_pad->letters[i];
        char const *found_word = find_word_in_dictionary(target_word, dictionary);
        if (found_word) {
            add_word_to_encodings(found_word, encoding_results);
        }
    }
    return encoding_results;
}



struct phone_encodings_t *
get_dictionary_matches_from_number(const char *phone_number, const struct dict_t *dictionary) {
    struct dial_pad_letters_t *dial_pad[4];

    if (strcmp(phone_number, "") == 0) {
        return new_phone_encodings();
    }

    dial_pad[2] = new_dial_pad(2, (const char *[]) {"a", "b"});
    dial_pad[3] = new_dial_pad(2, (const char *[]) {"d"});

    int dial_pad_index = phone_number[0] - '0';
    struct phone_encodings_t *result = find_encodings_from_set_in_dictionary(dial_pad[dial_pad_index], dictionary);

    free(dial_pad[2]);
    free(dial_pad[3]);

    return result;
}


void find_encodings(const char *phone_number,
                    const struct dict_t *dictionary,
                    struct phone_encodings_t *output_encodings
) {
    struct phone_encodings_t *found_mapping = get_dictionary_matches_from_number(phone_number, dictionary);
    copy_phone_encodings(output_encodings, found_mapping);
    delete_phone_encodings(found_mapping);
}



#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "phonecode.h"

struct dial_pad_letters_t {
    int length;
    char const **letters;
};

const char *find_word_in_dictionary(const struct dict_t *dictionary, const char *target_word) {
    const char *found_word = NULL;
    for(int j = 0; j < dictionary->size; j++) {
        if(strcmp(target_word, dictionary->words[j]) == 0){
            found_word = dictionary->words[j];
        }
    }
    return found_word;
}

char const * find_word_from_set_in_dictionary(const struct dial_pad_letters_t *dial_pad, const struct dict_t *dictionary) {
    char const *found_word = NULL;
    for(int i = 0; i < dial_pad->length && !found_word; i++ ){
        char const *target_word = dial_pad->letters[i];
        found_word = find_word_in_dictionary(dictionary, target_word);
    }
    return found_word;
}

struct dial_pad_letters_t *new_dial_pad(int n, const char** letters){
    struct dial_pad_letters_t *dial_pad = malloc(sizeof(struct dial_pad_letters_t));
    dial_pad->length = n;
    dial_pad->letters = malloc(sizeof(char *)*n);
    for(int i = 0; i < n; i++ ){
        dial_pad->letters[i] = strdup(letters[i]);
    }
    return dial_pad;
}

char const * number_corresponds_to_dictionary(const char *phone_number, const struct dict_t *dictionary) {
    struct dial_pad_letters_t *dial_pad [4];

    dial_pad[2] = new_dial_pad(2, (const char *[]) {"a", "b"});
    dial_pad[3] = new_dial_pad(2, (const char *[]) {"d"});

    return find_word_from_set_in_dictionary(dial_pad[phone_number[0]-'0'], dictionary);
}



void find_encodings(const char *phone_number,
                    const struct dict_t *dictionary,
                    struct phone_encodings_t *output_encodings
) {

    if (dictionary->size > 0) {
        char const *found_mapping = number_corresponds_to_dictionary(phone_number, dictionary);
        if (found_mapping) {
            strcpy(output_encodings->encodings[0], found_mapping);
            output_encodings->length = 1;
            return;
        }

        output_encodings->length = 0;

        strcpy(output_encodings->encodings[0], dictionary->words[0]);
    } else {
        output_encodings->length = 0;
    }
}
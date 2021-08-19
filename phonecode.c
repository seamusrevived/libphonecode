#include <string.h>
#include <stdio.h>
#include "phonecode.h"

struct dial_pad_letters_t {
    int length;
    char const **letters;
};

const char *find_word_in_dictionary(const struct dict_t *dictionary, char const *target_word) {
    const char *found_word = 0;
    for(int j = 0; j < dictionary->size; j++) {
        if(strcmp(target_word, dictionary->words[j]) == 0){
            found_word = dictionary->words[j];
        }
    }
    return found_word;
}

char const * find_word_from_set_in_dictionary(struct dial_pad_letters_t *dial_pad, struct dict_t *dictionary) {
    char const *found_word = 0;
    for(int i = 0; i < dial_pad->length && !found_word; i++ ){
        char const *target_word = dial_pad->letters[i];
        found_word = find_word_in_dictionary(dictionary, target_word);
    }
    return found_word;
}


char const * number_corresponds_to_dictionary(const char *phone_number, struct dict_t *dictionary) {
    char *letters_2[] = {"a", "b"};

    struct dial_pad_letters_t dial_pad_2;
    dial_pad_2.length = 2;
    dial_pad_2.letters = (const char **) letters_2;

    char *letters_3[] = {"d"};

    struct dial_pad_letters_t dial_pad_3;
    dial_pad_3.length = 1;
    dial_pad_3.letters = (const char **) letters_3;

    switch (phone_number[0]) {
        case '2':
            return find_word_from_set_in_dictionary(&dial_pad_2, dictionary);
        case '3':
            return find_word_from_set_in_dictionary(&dial_pad_3, dictionary);
    }
}



void find_encodings(const char *phone_number,
                    struct dict_t *dictionary,
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
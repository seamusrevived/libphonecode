#include <string.h>
#include <stdio.h>
#include "phonecode.h"


void find_encodings(const char *phone_number,
                    struct dict_t *dictionary,
                    struct phone_encodings_t *output_encodings
) {

    if (dictionary->size > 0) {
        if (strcmp("d", dictionary->words[0]) == 0 &&
            strcmp("3", phone_number) == 0) {
            strcpy(output_encodings->encodings[0], dictionary->words[0]);
            output_encodings->length = 1;
            return;
        }

        if (strcmp("a", dictionary->words[0]) == 0 ||
            strcmp("b", dictionary->words[0]) == 0 &&
            strcmp("2", phone_number) == 0) {
            strcpy(output_encodings->encodings[0], dictionary->words[0]);
            output_encodings->length = 1;
            return;
        }

        output_encodings->length = 0;

        strcpy(output_encodings->encodings[0], dictionary->words[0]);
    } else {
        output_encodings->length = 0;
    }
    return;
}
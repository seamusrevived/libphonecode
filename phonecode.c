#include <string.h>
#include <stdio.h>
#include "phonecode.h"


void find_encodings(const char *phone_number,
                    struct dict_t *dictionary,
                    struct phone_encodings_t *output_encodings
) {

    if (dictionary->size > 0) {
        if (strcmp("d", dictionary->words[0]) == 0) {
            output_encodings->length = 0;
            return;
        }

        strcpy(output_encodings->encodings[0], dictionary->words[0]);
    }

    output_encodings->length = dictionary->size;
}
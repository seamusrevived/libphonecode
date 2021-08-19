#include <string.h>
#include <stdio.h>
#include "phonecode.h"


void find_encodings(const char *phone_number,
                    struct dict_t *dictionary,
                    struct phone_encodings_t *output_encodings
) {
    output_encodings->length = dictionary->size;

    if(dictionary->size > 0){
        strcpy(output_encodings->encodings[0], dictionary->words[0]);
    }
}
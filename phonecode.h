#ifndef LIBPHONECODE_PHONECODE_H
#define LIBPHONECODE_PHONECODE_H


#include "phone_encodings.h"

struct dict_t {
    unsigned int size;
    char const **words;
};



void find_encodings(const char *phone_number, const struct dict_t *dictionary, struct phone_encodings_t *output_encodings);


#endif //LIBPHONECODE_PHONECODE_H

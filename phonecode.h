#ifndef LIBPHONECODE_PHONECODE_H
#define LIBPHONECODE_PHONECODE_H

#include "string_coll.h"

typedef struct dict_t dict_t;

struct dict_t {
    size_t size;
    char const **strings;
};

void find_encodings(const char *, const dict_t *, string_collection_t *);

#endif //LIBPHONECODE_PHONECODE_H

#ifndef LIBPHONECODE_PHONECODE_H
#define LIBPHONECODE_PHONECODE_H


struct dict_t {
    int size;
    char const **words;
};

struct phone_encodings_t {
    int length;
    char **encodings;
};

void find_encodings(const char *phone_number, const struct dict_t *dictionary, struct phone_encodings_t *output_encodings);


#endif //LIBPHONECODE_PHONECODE_H

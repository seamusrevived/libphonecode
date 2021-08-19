#ifndef LIBPHONECODE_PHONE_ENCODINGS_H
#define LIBPHONECODE_PHONE_ENCODINGS_H

struct phone_encodings_t {
    int length;
    char **encodings;
};

void delete_phone_encodings(struct phone_encodings_t *);

struct phone_encodings_t *new_phone_encodings();

void copy_phone_encodings(struct phone_encodings_t *, const struct phone_encodings_t *);

void add_word_to_encodings(const char *, struct phone_encodings_t *);

#endif //LIBPHONECODE_PHONE_ENCODINGS_H
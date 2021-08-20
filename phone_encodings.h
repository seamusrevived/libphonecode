#ifndef LIBPHONECODE_PHONE_ENCODINGS_H
#define LIBPHONECODE_PHONE_ENCODINGS_H

struct phone_encodings_t {
    size_t size;
    char **encodings;
};

void delete_phone_encodings(struct phone_encodings_t *);

struct phone_encodings_t *new_phone_encodings();

void raw_copy_phone_encodings(struct phone_encodings_t *, const struct phone_encodings_t *);

void copy_phone_encodings(struct phone_encodings_t *, const struct phone_encodings_t *);

void add_word_to_encodings(const char *, struct phone_encodings_t *);

void cross_merge_encodings(struct phone_encodings_t *acc, const struct phone_encodings_t *enc);

void add_encodings(struct phone_encodings_t *, const struct phone_encodings_t *);

#endif //LIBPHONECODE_PHONE_ENCODINGS_H

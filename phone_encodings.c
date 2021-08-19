#include <malloc.h>
#include <string.h>
#include "phone_encodings.h"

struct phone_encodings_t *new_phone_encodings() {
    struct phone_encodings_t *encodings = malloc(sizeof(struct phone_encodings_t));
    encodings->length = 0;
}

void resize_encodings(struct phone_encodings_t *dst, unsigned int new_size);

void delete_phone_encodings(struct phone_encodings_t *phone_encodings) {
    if (phone_encodings->length > 0) {
        for (int i = 0; i < phone_encodings->length; i++) {
            free(phone_encodings->encodings[i]);
        }
        free(phone_encodings->encodings);
    }
    free(phone_encodings);
}


void copy_phone_encodings(struct phone_encodings_t *dst, const struct phone_encodings_t *src) {
    resize_encodings(dst, src->length);

    for (int i = 0; i < src->length; i++) {
        free(dst->encodings[i]);
        dst->encodings[i] = strdup(src->encodings[i]);
    }
}

void grow_encodings(struct phone_encodings_t *dst, unsigned int new_size) {
    char **old_encodings = dst->encodings;
    dst->encodings = malloc(sizeof(char *) * new_size);
    memcpy(dst->encodings, old_encodings, sizeof(char *) * dst->length);
    for (unsigned int i = dst->length; i < new_size; i++) {
        dst->encodings[i] = malloc(sizeof(char));
        dst->encodings[i][0] = '\0';
    }
    if(dst->length > 0){
        free(old_encodings);
    }
    dst->length = new_size;
}

void shrink_encodings(struct phone_encodings_t *dst, unsigned int new_size) {
    for (unsigned int i = new_size; i < dst->length; i++) {
        free(dst->encodings[i]);
    }
    dst->length = new_size;
}

void resize_encodings(struct phone_encodings_t *dst, unsigned int new_size) {
    if (dst->length < new_size) {
        grow_encodings(dst, new_size);
    } else {
        shrink_encodings(dst, new_size);
    }
}

void unchecked_copy_phone_encodings(struct phone_encodings_t *dst, const struct phone_encodings_t *src) {
    for (int i = 0; i < src->length; i++) {
        strcpy(dst->encodings[i], src->encodings[i]);
    }
    dst->length = src->length;
}


void add_word_to_encodings(const char *found_word, struct phone_encodings_t *encoding_results) {
    char **old_memory = encoding_results->encodings;
    int n_existing_words = encoding_results->length;

    encoding_results->encodings = malloc(sizeof(const char *) * (n_existing_words + 1));
    if (n_existing_words != 0) {
        memcpy(encoding_results->encodings, old_memory, sizeof(char *) * n_existing_words);
        free(old_memory);
    }
    encoding_results->encodings[n_existing_words] = strdup(found_word);
    encoding_results->length += 1;
}

void merge_encodings(struct phone_encodings_t *acc, const struct phone_encodings_t *enc) {
    copy_phone_encodings(acc, enc);
}

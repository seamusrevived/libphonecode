#include <malloc.h>
#include <string.h>
#include "phone_encodings.h"

struct phone_encodings_t *new_phone_encodings() {
    struct phone_encodings_t *encodings = malloc(sizeof(struct phone_encodings_t));
    encodings->length = 0;
}

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
    dst->length = src->length;
    for (int i = 0; i < src->length; i++) {
        strcpy(dst->encodings[i], src->encodings[i]);
    }
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
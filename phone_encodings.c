#include <malloc.h>
#include <string.h>
#include "phone_encodings.h"

void replace_and_free_str(char **dst, const char *src) {
    char *old_memory = *dst;
    *dst = strdup(src);
    free(old_memory);
}

struct phone_encodings_t *new_phone_encodings() {
    struct phone_encodings_t *encodings = malloc(sizeof(struct phone_encodings_t));
    encodings->size = 0;
    return encodings;
}

void resize_encodings(struct phone_encodings_t *dst, unsigned int new_size);

void delete_phone_encodings(struct phone_encodings_t *phone_encodings) {
    if (phone_encodings->size > 0) {
        for (unsigned int i = 0; i < phone_encodings->size; i++) {
            free(phone_encodings->encodings[i]);
        }
        free(phone_encodings->encodings);
    }
    free(phone_encodings);
}

void grow_encodings(struct phone_encodings_t *dst, unsigned int new_size) {
    char **old_encodings = dst->encodings;
    dst->encodings = malloc(sizeof(char *) * new_size);
    memcpy(dst->encodings, old_encodings, sizeof(char *) * dst->size);
    for (unsigned int i = dst->size; i < new_size; i++) {
        dst->encodings[i] = malloc(sizeof(char));
        dst->encodings[i][0] = '\0';
    }
    if (dst->size > 0) {
        free(old_encodings);
    }
    dst->size = new_size;
}

void shrink_encodings(struct phone_encodings_t *dst, unsigned int new_size) {
    for (unsigned int i = new_size; i < dst->size; i++) {
        free(dst->encodings[i]);
    }
    dst->size = new_size;
}

void resize_encodings(struct phone_encodings_t *dst, unsigned int new_size) {
    if (dst->size < new_size) {
        grow_encodings(dst, new_size);
    } else {
        shrink_encodings(dst, new_size);
    }
}

void raw_copy_phone_encodings(struct phone_encodings_t *dst, const struct phone_encodings_t *src) {
    for (unsigned int i = 0; i < src->size; i++) {
        strcpy(dst->encodings[i], src->encodings[i]);
    }
    dst->size = src->size;
}

void copy_phone_encodings(struct phone_encodings_t *dst, const struct phone_encodings_t *src) {
    resize_encodings(dst, src->size);

    for (int i = 0; i < src->size; i++) {
        free(dst->encodings[i]);
        dst->encodings[i] = strdup(src->encodings[i]);
    }
}

void add_word_to_encodings(const char *found_word, struct phone_encodings_t *encoding_results) {
    char **old_memory = encoding_results->encodings;
    unsigned int n_existing_words = encoding_results->size;

    encoding_results->encodings = malloc(sizeof(const char *) * (n_existing_words + 1));
    if (n_existing_words != 0) {
        memcpy(encoding_results->encodings, old_memory, sizeof(char *) * n_existing_words);
        free(old_memory);
    }
    encoding_results->encodings[n_existing_words] = strdup(found_word);
    encoding_results->size += 1;
}

void add_encodings(struct phone_encodings_t *dst, const struct phone_encodings_t *src) {
    unsigned int dst_offset = dst->size;
    resize_encodings(dst, src->size + dst->size);

    for (unsigned int i = 0; i < src->size; i++) {
        dst->encodings[i+dst_offset] = strdup(src->encodings[i]);
    }
}


void append_string_with_word(char **acc_encoding, const char *word_to_append) {
    unsigned int dst_len = strlen(*acc_encoding);
    unsigned int src_len = strlen(word_to_append);

    char *new_encoding = malloc(sizeof(char) * (dst_len + src_len + 1));
    new_encoding[0] = '\0';
    if (dst_len > 0) {
        strcpy(new_encoding, *acc_encoding);
        strcat(new_encoding, " ");
    }
    strcat(new_encoding, word_to_append);

    replace_and_free_str(acc_encoding, new_encoding);
}

unsigned int max(unsigned int x, unsigned int y) {
    if (x > y) {
        return x;
    }
    return y;
}


void duplicate_ith_of_n_encodings_m_times(struct phone_encodings_t *acc,
                                          unsigned int i,
                                          unsigned int n,
                                          unsigned int m) {
    for (unsigned int j = 1; j < m; j++) {
        unsigned int acc_index = i + j * n;
        replace_and_free_str(&acc->encodings[acc_index], acc->encodings[i]);
    }
}

void duplicate_n_encodings_m_times(struct phone_encodings_t *acc,
                                   unsigned int n,
                                   unsigned int m) {
    for (unsigned int i = 0; i < n; i++) {
        duplicate_ith_of_n_encodings_m_times(acc, i, n, m);
    }
}

void cross_append_ith_of_n_encodings_with_encodings(const struct phone_encodings_t *acc,
                                                    unsigned int i,
                                                    unsigned int n_initial_acc_encodings,
                                                    const struct phone_encodings_t *enc) {
    for (unsigned int j = 0; j < enc->size; j++) {
        unsigned int acc_index = i + j * n_initial_acc_encodings;
        append_string_with_word(&acc->encodings[acc_index], enc->encodings[j]);
    }
}

void cross_merge_encodings(struct phone_encodings_t *acc, const struct phone_encodings_t *enc) {
    unsigned int n_initial_acc_encodings = max(1, acc->size);
    unsigned int n_encodings_to_cross_append = enc->size;
    unsigned int minimum_new_accumulator_size = n_initial_acc_encodings * n_encodings_to_cross_append;

    if (acc->size < minimum_new_accumulator_size) {
        resize_encodings(acc, minimum_new_accumulator_size);
    }

    duplicate_n_encodings_m_times(acc, n_initial_acc_encodings, n_encodings_to_cross_append);

    for (unsigned int i = 0; i < n_initial_acc_encodings; i++) {
        cross_append_ith_of_n_encodings_with_encodings(acc, i, n_initial_acc_encodings, enc);
    }
}

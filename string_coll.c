#include <malloc.h>
#include <string.h>
#include "string_coll.h"
#include "util.h"

void __replace_and_free_str(char **, const char *);

void __grow_string_collection(string_collection_t *dst, size_t new_size);

void __shrink_string_collection(string_collection_t *dst, size_t new_size);

void __join_strings(char **, const char *);


string_collection_t *new_string_collection() {
    string_collection_t *coll = malloc(sizeof(string_collection_t));
    coll->size = 0;
    return coll;
}

void delete_string_collection(string_collection_t *coll) {
    if (coll->size > 0) {
        for (unsigned int i = 0; i < coll->size; i++) {
            free(coll->strings[i]);
        }
        free(coll->strings);
    }
    free(coll);
}

void raw_copy_string_collection(
        string_collection_t *dst,
        const string_collection_t *src
) {
    for (unsigned int i = 0; i < src->size; i++) {
        strcpy(dst->strings[i], src->strings[i]);
    }
    dst->size = src->size;
}


void copy_string_collection(
        string_collection_t *dst,
        const string_collection_t *src
) {
    resize_string_collection(dst, src->size);
    for (int i = 0; i < src->size; i++) {
        __replace_and_free_str(&dst->strings[i], src->strings[i]);
    }
}

void resize_string_collection(
        string_collection_t *dst,
        size_t new_size
) {
    if (dst->size < new_size) {
        __grow_string_collection(dst, new_size);
    } else {
        __shrink_string_collection(dst, new_size);
    }
}

void __grow_string_collection(
        string_collection_t *dst,
        size_t new_size
) {
    char **old_strings = dst->strings;
    dst->strings = malloc(sizeof(char *) * new_size);
    memcpy(dst->strings, old_strings, sizeof(char *) * dst->size);
    for (unsigned int i = dst->size; i < new_size; i++) {
        dst->strings[i] = malloc(sizeof(char));
        dst->strings[i][0] = '\0';
    }
    if (dst->size > 0) {
        free(old_strings);
    }
    dst->size = new_size;
}

void __shrink_string_collection(
        string_collection_t *dst,
        size_t new_size
) {
    for (unsigned int i = new_size; i < dst->size; i++) {
        free(dst->strings[i]);
    }
    dst->size = new_size;
}


void concat_string_collections(
        string_collection_t *dst,
        const string_collection_t *src
) {
    unsigned int dst_offset = dst->size;
    resize_string_collection(dst, src->size + dst->size);

    for (unsigned int i = 0; i < src->size; i++) {
        __replace_and_free_str(&dst->strings[i + dst_offset], src->strings[i]);
    }
}

void add_string_to_string_collection(
        const char *string,
        string_collection_t *coll
) {
    size_t new_size = coll->size + 1;
    __grow_string_collection(coll, new_size);
    __replace_and_free_str(&coll->strings[new_size - 1], string);
}


void duplicate_ith_of_n_strings_m_times(
        string_collection_t *acc,
        size_t i,
        size_t n,
        size_t m
) {
    for (size_t j = 1; j < m; j++) {
        size_t acc_index = i + j * n;
        __replace_and_free_str(&acc->strings[acc_index], acc->strings[i]);
    }
}

void __replace_and_free_str(char **dst, const char *src) {
    char *old_memory = *dst;
    *dst = strdup(src);
    free(old_memory);
}

void
duplicate_n_strings_m_times(
        string_collection_t *acc,
        size_t n,
        size_t m
) {
    for (size_t i = 0; i < n; i++) {
        duplicate_ith_of_n_strings_m_times(acc, i, n, m);
    }
}

void cross_join_ith_of_n_strings(
        const string_collection_t *acc,
        size_t i,
        size_t n,
        const string_collection_t *coll
) {
    for (size_t j = 0; j < coll->size; j++) {
        size_t acc_index = i + j * n;
        __join_strings(&acc->strings[acc_index], coll->strings[j]);
    }
}

void __join_strings(char **dst, const char *string) {
    unsigned int dst_len = strlen(*dst);
    unsigned int src_len = strlen(string);

    char *joined_string = malloc(sizeof(char) * (dst_len + src_len + 1));
    joined_string[0] = '\0';
    if (dst_len > 0) {
        strcpy(joined_string, *dst);
        strcat(joined_string, " ");
    }
    strcat(joined_string, string);

    __replace_and_free_str(dst, joined_string);
}

void cross_merge_strings(
        string_collection_t *acc,
        const string_collection_t *coll
) {
    unsigned int initial_acc_size = max(1, acc->size);
    unsigned int coll_size = coll->size;
    unsigned int min_acc_size = initial_acc_size * coll_size;

    if (acc->size < min_acc_size) {
        resize_string_collection(acc, min_acc_size);
    }

    duplicate_n_strings_m_times(acc, initial_acc_size, coll_size);

    for (unsigned int i = 0; i < initial_acc_size; i++) {
        cross_join_ith_of_n_strings(acc, i, initial_acc_size, coll);
    }
}

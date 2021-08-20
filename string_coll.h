#ifndef LIBPHONECODE_STRING_COLL_H
#define LIBPHONECODE_STRING_COLL_H

struct string_collection_t {
    size_t size;
    char **strings;
};

struct string_collection_t *new_string_collection();

void delete_string_collection(struct string_collection_t *coll);

void raw_copy_string_collection(struct string_collection_t *dst, const struct string_collection_t *src);

void copy_string_collection(struct string_collection_t *dst, const struct string_collection_t *src);

void add_string_to_string_collection(const char *string, struct string_collection_t *coll);

void cross_merge_strings(struct string_collection_t *acc, const struct string_collection_t *coll);

void concat_string_collections(struct string_collection_t *dst, const struct string_collection_t *src);

#endif //LIBPHONECODE_STRING_COLL_H

#ifndef LIBPHONECODE_STRING_COLL_H
#define LIBPHONECODE_STRING_COLL_H

typedef struct string_collection_t string_collection_t;

struct string_collection_t {
    size_t size;
    char **strings;
};

string_collection_t *new_string_collection();

void delete_string_collection(string_collection_t *coll);

void raw_copy_string_collection(string_collection_t *dst, const string_collection_t *src);

void copy_string_collection(string_collection_t *dst, const string_collection_t *src);

void resize_string_collection(string_collection_t *dst, size_t new_size);

void concat_string_collections(string_collection_t *dst, const string_collection_t *src);

void add_string_to_string_collection(const char *string, string_collection_t *coll);

void cross_merge_strings(string_collection_t *acc, const string_collection_t *coll);

#endif //LIBPHONECODE_STRING_COLL_H

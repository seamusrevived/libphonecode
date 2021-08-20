#ifndef LIBPHONECODE_TESTUTILS_H
#define LIBPHONECODE_TESTUTILS_H

extern "C" {
#include <phonecode.h>
};

char **initialize_strings_buffer(size_t max_output_length, size_t max_string_length);

string_collection_t *initialize_phone_encodings();

dict_t *initialize_dictionary(size_t size, const char **words);

#endif //LIBPHONECODE_TESTUTILS_H

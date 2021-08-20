//
// Created by seamus on 8/19/2021.
//

#ifndef LIBPHONECODE_UTILS_H
#define LIBPHONECODE_UTILS_H

char **initialize_strings_buffer(size_t max_output_length, size_t max_string_length);
struct phone_encodings_t *initialize_phone_encodings();

struct dict_t *initialize_dictionary(size_t size, const char **words);

#endif //LIBPHONECODE_UTILS_H

#include <cstdlib>
#include <string.h>

char **initialize_strings_buffer(int max_output_length, int max_string_length) {
    char **output = (char **) malloc(sizeof(char *) * max_output_length);
    for (int i = 0; i < max_output_length; i++) {
        output[i] = (char *) malloc(sizeof(char) * max_string_length);
        memset(output[i], '\0', max_string_length);
    }
    return output;
}
#include <gtest/gtest.h>
#include "utils.h"

extern "C" {
#include "phonecode.h"
}

const int MAX_OUTPUT_LENGTH = 1028;
const int MAX_STRING_LENGTH = 256;

TEST(libphonecode, empty_phone_number_no_dictionary_returns_0_results) {
    struct dict_t dict{
            .size = 0,
    };

    struct phone_encodings_t output{
            .length = -1,
            .encodings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    find_encodings("", &dict, &output);

    EXPECT_EQ(0, output.length);
}



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
            .length = 0,
            .encodings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    find_encodings("", &dict, &output);

    EXPECT_EQ(0, output.length);
}


TEST(libphonecode, phone_number_2_with_dictionary_a_returns_1_result_a) {
    const char *expected_result = "a";
    const char *words[] = {expected_result};
    struct dict_t dict{
            .size = 1,
            .words = words
    };

    struct phone_encodings_t output{
            .length = 0,
            .encodings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    find_encodings("2", &dict, &output);

    EXPECT_EQ(1, output.length);
    EXPECT_STREQ(expected_result, output.encodings[0]);
}


TEST(libphonecode, phone_number_2_with_dictionary_b_returns_1_result_b) {
    const char *expected_result = "b";
    const char *words[] = {expected_result};
    struct dict_t dict{
            .size = 1,
            .words = words
    };

    struct phone_encodings_t output{
            .length = 0,
            .encodings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    find_encodings("2", &dict, &output);

    EXPECT_EQ(1, output.length);
    EXPECT_STREQ(expected_result, output.encodings[0]);
}


TEST(libphonecode, phone_number_2_with_dictionary_d_returns_0_results) {
    const char *words[] = {"d"};
    struct dict_t dict{
            .size = 1,
            .words = words
    };

    struct phone_encodings_t output{
            .length = 0,
            .encodings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    find_encodings("2", &dict, &output);

    EXPECT_EQ(0, output.length);
}

TEST(libphonecode, phone_number_3_with_dictionary_d_returns_1_result_of_d) {
    const char *words[] = {"d"};
    struct dict_t dict{
            .size = 1,
            .words = words
    };

    struct phone_encodings_t output{
            .length = 0,
            .encodings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    find_encodings("3", &dict, &output);

    EXPECT_EQ(1, output.length);
    EXPECT_STREQ("d", output.encodings[0]);
}

TEST(libphonecode, phone_number_2_with_dictionary_d_a_returns_1_result_of_a) {
    const char *words[] = {"d", "a"};
    struct dict_t dict{
            .size = 2,
            .words = words
    };

    struct phone_encodings_t output{
            .length = 0,
            .encodings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    find_encodings("2", &dict, &output);

    EXPECT_EQ(1, output.length);
    EXPECT_STREQ("a", output.encodings[0]);
}

TEST(libphonecode, phone_number_2_with_dictionary_a_b_returns_2_results_of_a_and_b) {
    const char *words[] = {"a", "b"};
    struct dict_t dict{
            .size = 2,
            .words = words
    };

    struct phone_encodings_t output{
            .length = 0,
            .encodings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    find_encodings("2", &dict, &output);

    EXPECT_EQ(2, output.length);
    EXPECT_STREQ("a", output.encodings[0]);
    EXPECT_STREQ("b", output.encodings[1]);
}

TEST(libphonecode, phone_number_22_with_dictionary_a_returns_1_result_of_a_a) {
    const char *words[] = {"a"};
    struct dict_t dict{
            .size = 1,
            .words = words
    };

    struct phone_encodings_t output{
            .length = MAX_OUTPUT_LENGTH,
            .encodings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    find_encodings("22", &dict, &output);

    EXPECT_EQ(1, output.length);
    EXPECT_STREQ("a a", output.encodings[0]);
}

TEST(libphonecode, phone_number_22_with_dictionary_a_b_returns_4_result_of_a_b_combos) {
    const char *words[] = {"a", "b"};
    struct dict_t dict{
            .size = 2,
            .words = words
    };

    struct phone_encodings_t output{
            .length = MAX_OUTPUT_LENGTH,
            .encodings = initialize_strings_buffer(MAX_OUTPUT_LENGTH, MAX_STRING_LENGTH)
    };

    find_encodings("22", &dict, &output);

    EXPECT_EQ(4, output.length);
    EXPECT_STREQ("a a", output.encodings[0]);
    EXPECT_STREQ("b a", output.encodings[1]);
    EXPECT_STREQ("a b", output.encodings[2]);
    EXPECT_STREQ("b b", output.encodings[3]);
}

#include <gtest/gtest.h>
#include "testutils.h"

extern "C" {
#include "phonecode.h"
}


TEST(libphonecode, empty_phone_number_no_dictionary_returns_0_results) {
    auto dict = initialize_dictionary(0, {});
    auto * output = initialize_phone_encodings();

    find_encodings("", dict, output);

    EXPECT_EQ(0, output->size);
}


TEST(libphonecode, phone_number_2_with_dictionary_a_returns_1_result_a) {
    auto expected_result = "a";
    const char *words[] = {expected_result};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("2", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ(expected_result, output->strings[0]);
}


TEST(libphonecode, phone_number_2_with_dictionary_b_returns_1_result_b) {
    auto expected_result = "b";
    const char *words[] = {expected_result};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("2", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ(expected_result, output->strings[0]);
}


TEST(libphonecode, phone_number_2_with_dictionary_d_returns_0_results) {
    const char *words[] = {"d"};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("2", dict, output);

    EXPECT_EQ(0, output->size);
}

TEST(libphonecode, phone_number_3_with_dictionary_d_returns_1_result_of_d) {
    const char *words[] = {"d"};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("3", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ("d", output->strings[0]);
}

TEST(libphonecode, phone_number_2_with_dictionary_d_a_returns_1_result_of_a) {
    const char *words[] = {"d", "a"};
    auto dict = initialize_dictionary(2, words);
    auto output = initialize_phone_encodings();

    find_encodings("2", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ("a", output->strings[0]);
}

TEST(libphonecode, phone_number_2_with_dictionary_a_b_returns_2_results_of_a_and_b) {
    const char *words[] = {"a", "b"};
    auto dict = initialize_dictionary(2, words);
    auto output = initialize_phone_encodings();

    find_encodings("2", dict, output);

    EXPECT_EQ(2, output->size);
    EXPECT_STREQ("a", output->strings[0]);
    EXPECT_STREQ("b", output->strings[1]);
}

TEST(libphonecode, phone_number_22_with_dictionary_a_returns_1_result_of_a_a) {
    const char *words[] = {"a"};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("22", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ("a a", output->strings[0]);
}

TEST(libphonecode, phone_number_22_with_dictionary_a_b_returns_4_result_of_a_b_combos) {
    const char *words[] = {"a", "b"};
    auto dict = initialize_dictionary(2, words);
    auto output = initialize_phone_encodings();

    find_encodings("22", dict, output);

    EXPECT_EQ(4, output->size);
    EXPECT_STREQ("a a", output->strings[0]);
    EXPECT_STREQ("b a", output->strings[1]);
    EXPECT_STREQ("a b", output->strings[2]);
    EXPECT_STREQ("b b", output->strings[3]);
}

TEST(libphonecode, phone_number_22_with_dictionary_ab_returns_result_of_ab) {
    const char *words[] = {"ab"};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("22", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ("ab", output->strings[0]);
}

TEST(libphonecode, phone_number_22_with_dictionary_a_ab_returns_result_of_a_a_and_ab) {
    const char *words[] = {"a", "ab"};
    auto dict = initialize_dictionary(2, words);
    auto output = initialize_phone_encodings();

    find_encodings("22", dict, output);

    EXPECT_EQ(2, output->size);
    EXPECT_STREQ("a a", output->strings[0]);
    EXPECT_STREQ("ab", output->strings[1]);
}

TEST(libphonecode, phone_number_23456789_with_word_adgjmptw_has_one_match) {
    const char *words[] = {"adgjmptw"};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("23456789", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ("adgjmptw", output->strings[0]);
}

TEST(libphonecode, phone_number_23456789_with_word_behknqux_has_one_match) {
    const char *words[] = {"behknqux"};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("23456789", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ("behknqux", output->strings[0]);
}

TEST(libphonecode, phone_number_23456789_with_word_cfilorvy_has_one_match) {
    const char *words[] = {"cfilorvy"};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("23456789", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ("cfilorvy", output->strings[0]);
}

TEST(libphonecode, phone_number_79_with_word_sz_has_one_match) {
    const char *words[] = {"sz"};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("79", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ("sz", output->strings[0]);
}

TEST(libphonecode, phone_number_2323_with_word_ad_has_one_match_ad_ad) {
    const char *words[] = {"ad"};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("2323", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ("ad ad", output->strings[0]);
}

TEST(libphonecode, phone_number_23_withgarbage_with_word_ad_has_one_match_ad) {
    const char *words[] = {"ad"};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("-(23) (#*()@", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ("ad", output->strings[0]);
}
TEST(libphonecode, phone_number_2_with_word_A_has_one_match_A) {
    const char *words[] = {"A"};
    auto dict = initialize_dictionary(1, words);
    auto output = initialize_phone_encodings();

    find_encodings("2", dict, output);

    EXPECT_EQ(1, output->size);
    EXPECT_STREQ("A", output->strings[0]);
}
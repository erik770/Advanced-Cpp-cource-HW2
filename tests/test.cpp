#include <gtest/gtest.h>
#include "word_search_interface.h"

TEST(word_generation, word_generation) {
    char *string_of_words = create_words();
    EXPECT_FALSE(string_of_words == NULL);
    free(string_of_words);
}

TEST(word_generation, word_generation_size) {
    char *string_of_words = create_words();
    EXPECT_TRUE((strlen(string_of_words) > MIN_SIZE) && (strlen(string_of_words) < MAX_SIZE));
    free(string_of_words);
}

TEST(word_counter, word_counter_invalid_input) {
    char *pseudo_string = NULL;
    size_t number_of_words = word_counter(pseudo_string);
    EXPECT_TRUE(number_of_words == 0);
}

TEST(array_creating, array_creating_invalid_input) {
    char *pseudo_string = NULL;
    char **arr = create_array_of_words(pseudo_string);
    EXPECT_TRUE(arr == NULL);
}

TEST(array_creating, array_creating) {
    char *string_of_words = create_words();
    size_t number_of_words = word_counter(string_of_words);
    char **arr = create_array_of_words(string_of_words);
    for (size_t i = 0; i < number_of_words; ++i) {
        EXPECT_TRUE(arr[i] != NULL);
    }
    EXPECT_TRUE(arr != NULL);
    for (size_t i = 0; i < number_of_words; ++i) {
        free(arr[i]);
    }
    free(string_of_words);
    free(arr);
}

TEST(array_creating, array_creating_const) {
    char *string_of_words = create_words();
    size_t number_of_words = word_counter(string_of_words);
    char *copy = (char *) malloc(MAX_SIZE * sizeof(char));
    copy = strcpy(copy, string_of_words);
    char **arr = create_array_of_words(string_of_words);
    EXPECT_TRUE(strcmp(copy, string_of_words) == 0);
    for (size_t i = 0; i < number_of_words; ++i) {
        free(arr[i]);
    }
    free(arr);
    free(copy);
    free(string_of_words);
}

TEST(max_len_word, max_len_word_invalid_input) {
    char *pseudo_string = NULL;
    char *longest_word = find_longest_word(pseudo_string);
    EXPECT_TRUE(longest_word == NULL);
}


TEST(max_len_word, max_len_word) {
    char *string_of_words = create_words();
    size_t number_of_words = word_counter(string_of_words);
    char **arr = create_array_of_words(string_of_words);
    char *longest_word = find_longest_word(string_of_words);
    for (size_t i = 0; i < number_of_words; ++i) {
        EXPECT_TRUE(strlen(longest_word) >= strlen(arr[i]));
    }
    for (size_t i = 0; i < number_of_words; ++i) {
        free(arr[i]);
    }
    free(arr);
    free(longest_word);
    free(string_of_words);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

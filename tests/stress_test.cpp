#include <gtest/gtest.h>
#include "word_search_interface.h"
#include <ctime>

#define NUM_OF_TESTS 15

int main() {
    double timer = 0;

    for (size_t i = 0; i < NUM_OF_TESTS; i++) {
        char *string_of_words = create_words();

        clock_t begin = clock();
        char *longest_word = find_longest_word(string_of_words);
        clock_t end = clock();

        timer += (double) (end - begin) / CLOCKS_PER_SEC;

        free(string_of_words);
        free(longest_word);
    }
    double avg_time = timer / NUM_OF_TESTS;
    std::cout << "average time: " << avg_time << std::endl;
    return 0;
}

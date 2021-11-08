#include "word_search_interface.h"

char *find_longest_word(char *string_of_words) {
    if (string_of_words == NULL) {
        return NULL;
    }

    char *longest_word = (char *) calloc(BUFF_SIZE, sizeof(char));
    if (longest_word == NULL) {
        return NULL;
    }

    char *current_word = (char *) malloc(BUFF_SIZE * sizeof(char));
    if (current_word == NULL) {
        free(longest_word);
        return NULL;
    }

    size_t i = 0;

    while (true) {
        if (word_cpy(current_word, string_of_words, i) != 0){
            free(longest_word);
            free(current_word);
            return NULL;
        }
        i = i + strlen(current_word) + 1;

        if (strlen(current_word) > strlen(longest_word)) {
            strcpy(longest_word, current_word);
        }
        if (string_of_words[i - 1] == '\0') {
            break;
        }
    }

    free(current_word);
    return longest_word;
}

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
        return NULL;
    }

    size_t i = 0, j = 0;

    while (string_of_words[i] != '\0') {
        while (string_of_words[i] != ' ') {
            current_word[j] = string_of_words[i];
            i++;
            j++;
        }
        current_word[j] = '\0';
        j = 0;
        i++;
        if (strlen(current_word) > strlen(longest_word)) {
            strcpy(longest_word, current_word);
        }
    }

    free(current_word);
    return longest_word;
}

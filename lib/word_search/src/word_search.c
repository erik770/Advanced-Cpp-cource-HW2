#include "word_search_interface.h"

char* find_longest_word(char* string_of_words) {
    if(string_of_words == NULL) {
        return NULL;
    }
    printf("%s\n", string_of_words);

    char* longest_word = (char*) malloc(strlen(string_of_words) * sizeof(char));
    if (longest_word == NULL) {
        free(string_of_words);
        return NULL;
    }

    char* word = strtok(string_of_words, " ");
    if (word == NULL) {
        free(longest_word);
        return string_of_words;
    }
    strcpy(longest_word, word);
    while (word != NULL) {

        if(strlen(longest_word) < strlen(word)){
            strcpy(longest_word, word);
        }
        if (!strcmp(longest_word, "")){
            continue;
        }
        word = strtok(NULL, " ");
    }
//    free(string_of_words);
//    printf("\n%lu\n%s\n", strlen(longest_word), longest_word);

    return longest_word;
}
#include "utils.h"

char *create_words() {
    srand(time(NULL));
    size_t size = rand() % (MAX_SIZE - MIN_SIZE + 1) + MIN_SIZE;

    char *words = (char *) malloc(size * sizeof(char));
    if (words == NULL) {
        return NULL;
    }
    words[0] = SYMBOLS[rand() % (strlen(SYMBOLS) - NUMB_OF_SPACES)];
    for (size_t i = 1; i < size - 1; i++) {
        words[i] = SYMBOLS[rand() % strlen(SYMBOLS)];
        if (words[i] == ' ' && words[i - 1] == ' ') {
            words[i] = SYMBOLS[rand() % (strlen(SYMBOLS) - NUMB_OF_SPACES)];
        }
    }
    if (words[size - 2] == ' ') {
        words[size - 2] = '\0';
    } else {
        words[size - 1] = '\0';
    }
    return words;
}

size_t word_counter(char *string_of_words) {
    if (string_of_words == NULL) {
        return 0;
    }

    size_t word_counter = 0;
    size_t i = 0;
    while (string_of_words[i] != '\0') {
        if (string_of_words[i] == ' ') {
            word_counter++;
        }
        i++;
    }
    word_counter++;

    return word_counter;
}

char **create_array_of_words(char *string_of_words) {
    if (string_of_words == NULL) {
        return NULL;
    }

    size_t words_count = word_counter(string_of_words);
    if (words_count == 0) {
        return NULL;
    }
    size_t j = 0, k = 0, h = 0;
    char **words_arr = (char **) malloc(words_count * sizeof(char *));
    if (words_arr == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < words_count; ++i) {
        words_arr[i] = (char *) malloc(BUFF_SIZE * sizeof(char));
        if (words_arr[i] == NULL) {
            for (size_t l = i; l > 0; l--) {
                free(words_arr[l - 1]);
            }
            free(words_arr);
            return NULL;
        }
    }

    while (string_of_words[j] != '\0') {
        if (string_of_words[j] == ' ') {
            words_arr[k][h] = '\0';
            ++j;
            ++k;
            h = 0;
        } else {
            words_arr[k][h++] = string_of_words[j++];
        }
    }
    words_arr[k++][h++] = '\0';
    return words_arr;
}

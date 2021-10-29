#include "utils.h"

char *create_words() {
    srand(time(NULL));
    size_t size = rand() % (MAX_SIZE - MIN_SIZE + 1) + MIN_SIZE;
//    printf("%d\n", size);
    char *words = (char *) malloc(size * sizeof(char));
    if (words == NULL) {
        return NULL;
    }
    words[0] = SYMBOLS[rand() % (strlen(SYMBOLS) - NUMB_OF_SPACES)];
    for (size_t i = 1; i < size - 1; i++) {
        words[i] = SYMBOLS[rand() % strlen(SYMBOLS)];
        if(words[i] == ' ' && words[i-1] == ' '){
            words[i] = SYMBOLS[rand() % (strlen(SYMBOLS) - NUMB_OF_SPACES)];
        }
    }
    if (words[size - 2] == ' '){
        words[size - 2] = '\0';
    }else {
        words[size - 1] = '\0';
    }
    return words;
}

size_t word_counter(const char* string_of_words) {
    if(string_of_words == NULL) {
        return -1;
    }
//    printf("%s\n", string_of_words);
    char* copy = (char*)malloc(sizeof(char) *(strlen(string_of_words)+1));
    if (copy == NULL) {
        return -1;
    }
    strcpy(copy,string_of_words);
    size_t word_counter = 0;

    char* word = strtok(copy, " ");
    if (word == NULL) {
        free(copy);
        return -1;
    }
    while (word != NULL) {

        word = strtok(NULL, " ");
        word_counter++;
    }
    free(copy);
//    printf("%lu", word_counter);
    return word_counter;
}

//char* delete_spaces (char* string_of_words){
//
//}

char** create_array_of_words(char* string_of_words) {
//    if(string_of_words == NULL) {
//        return NULL;
//    }
//    size_t number_of_words = word_counter(string_of_words);
//    if (number_of_words == -1) {
//        free(string_of_words);
//        return NULL;
//    }
//
//    char** array_of_words = (char**) malloc(number_of_words * sizeof (char*));
//    if(array_of_words == NULL) {
//        free(string_of_words);
//        return NULL;
//    }
//    for (size_t i = 0; i < number_of_words; i++) {
//        array_of_words[i] = (char*) malloc(BUFF_SIZE *sizeof(char));
//        if(array_of_words[i] == NULL){
//            for (; i > 0 ; i--){
//                free(array_of_words[i-1]);
//            }
//            free(array_of_words);
//            free(string_of_words);
//            return NULL;
//        }
//    }
//
//    char* copy = (char*)malloc(sizeof(char) *(strlen(string_of_words)+1));
//    if (copy == NULL) {
//        for (size_t i = 0; i < number_of_words ; i++){
//            free(array_of_words[i]);
//        }
//        free(array_of_words);
//        free(string_of_words);
//        return NULL;
//    }
//    strcpy(copy,string_of_words);
//    size_t counter = 0;
//    array_of_words[counter] = strtok(copy, " ");
//    if(array_of_words[0] == NULL) {
//        for (size_t i = 0; i < number_of_words; i++){
//            free(array_of_words[0]);
//        }
//        free(array_of_words);
//        return NULL;
//    }
//
//    while (array_of_words[counter] != NULL){
//        counter++;
//        array_of_words[counter] = strtok(NULL, " ");
//    }
//
//    if (counter != number_of_words) {
//        for (; counter > 0 ; counter--){
//            free(array_of_words[counter-1]);
//        }
//        free(array_of_words);
//        return NULL;
//    }
////    free(string_of_words);
//    printf("%lu", counter);
//    for(size_t i = 0; i <number_of_words; i++){
//        printf("\n%s", array_of_words[i]);
//    }
//    free(copy);
//    return array_of_words;


    printf("%s\n", string_of_words);

    size_t words_count = word_counter(string_of_words);
    size_t j = 0, k = 0, h = 0;
    char** words_arr = (char**)malloc(words_count * sizeof(char *));

    for(size_t i = 0; i < words_count; ++i) {
        words_arr[i] = (char*)malloc(BUFF_SIZE * sizeof(char));
    }

    while(string_of_words[j] != '\0') {
        if(string_of_words[j] == ' ') {
            words_arr[k][h] = '\0';
            ++j;
            ++k;
            h = 0;
        }
        else {
            words_arr[k][h++] = string_of_words[j++];
        }
    }
    words_arr[k++][h++] = '\0';

    for(size_t i = 0; i< words_count;i++) {
        printf("%s\n",words_arr[i]);
    }

    return words_arr;
}



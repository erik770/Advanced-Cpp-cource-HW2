#include "word_search_interface.h"

int main () {
//    char*a = find_longest_word(create_words());
//    char* a = find_longest_word(create_words());
    char* words = create_words();
    char* a = find_longest_word(words);
    printf("%s", a);

//    char** a = create_array_of_words(words);
//    size_t b =word_counter(words);
//    for(size_t i = 0; i < b; i++) {
//        free(a[i]);
//    }
    free(a);
//    word_counter(words);
    free(words);
    return 0;
}
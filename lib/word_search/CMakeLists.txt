add_library(word_search STATIC src/word_search.c)

target_include_directories(word_search PUBLIC include)
target_link_libraries(word_search PUBLIC utils)

add_library(utils STATIC src/utils.c include/utils.h)

target_include_directories(utils PUBLIC include)
#target_link_libraries(word_search PUBLIC utils)
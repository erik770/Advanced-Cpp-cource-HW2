add_library(utils STATIC src/utils.c include/utils.h)

target_include_directories(utils PUBLIC include)

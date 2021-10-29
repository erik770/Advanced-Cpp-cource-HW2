#pragma once

#include "stdio.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define SYMBOLS "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm     "
#define NUMB_OF_SPACES 5
//#define MIN_SIZE 131072   // 128*1024 128 кБайт
//#define MAX_SIZE 1048576   //Мбайт
#define MIN_SIZE 50  // 128*1024 128 кБайт
#define MAX_SIZE 150   //Мбайт
#define BUFF_SIZE 500

char *create_words();

bool close_file(FILE *f);

FILE *open_file(const char *path);

size_t word_counter(const char *string_of_words);

char **create_array_of_words(char *string_of_words);

int write_words_to_file(char *words, const char *file_path);





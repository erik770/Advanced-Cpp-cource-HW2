#include "word_search_interface.h"


typedef struct {
    long mtype;
    char mtext[BUFF_SIZE];
} message_buff;

char *find_longest_word(char *string_of_words) {
    if (string_of_words == NULL) {
        return NULL;
    }
    char **words_array = create_array_of_words(string_of_words);
    if (words_array == NULL) {
        free(string_of_words);
        return NULL;
    }
    size_t number_of_words = word_counter(string_of_words);
    size_t number_of_procs = sysconf(_SC_NPROCESSORS_ONLN);
    size_t part_size = number_of_words / number_of_procs;
    int status;

    key_t key = IPC_PRIVATE;
    int q_id = msgget(key, 0660 | IPC_CREAT);

    pid_t pids[number_of_procs];
    for (size_t k = 0; k < number_of_procs; ++k) {
        pids[k] = fork();
        if (pids[k] == 0) {
            char *longest_word = NULL;
            size_t max_len = 0;
            if (k != number_of_procs - 1) {
                for (size_t j = k * part_size; j < (k + 1) * part_size; ++j) {
                    if (strlen(words_array[j]) >= max_len) {
                        max_len = strlen(words_array[j]);
                        if (longest_word != NULL) {
                            free(longest_word);
                        }
                        longest_word = (char *) malloc(BUFF_SIZE * sizeof(char));
                        if (longest_word == NULL) {
                            for (size_t i = 0; i < number_of_words; i++) {
                                if (words_array[i] != NULL)
                                    free(words_array[i]);
                            }
                            free(words_array);
                            free(string_of_words);
                            exit(EXIT_FAILURE);
                        }
                        strcpy(longest_word, words_array[j]);
                    }
                }


            } else {
                for (size_t j = k * part_size; j < number_of_words; ++j) {
                    if (strlen(words_array[j]) >= max_len) {
                        max_len = strlen(words_array[j]);
                        if (longest_word != NULL) {
                            free(longest_word);
                        }
                        longest_word = (char *) malloc(BUFF_SIZE * sizeof(char));
                        if (longest_word == NULL) {
                            for (size_t i = 0; i < number_of_words; i++) {
                                if (words_array[i] != NULL)
                                    free(words_array[i]);
                            }
                            free(words_array);
                            free(string_of_words);
                            exit(EXIT_FAILURE);
                        }
                        strcpy(longest_word, words_array[j]);
                    }
                }
            }

            if (longest_word == NULL) {
                for (size_t i = 0; i < number_of_words; i++) {
                    if (words_array[i] != NULL)
                        free(words_array[i]);
                }
                free(words_array);
                free(string_of_words);
                exit(EXIT_FAILURE);
            }

            message_buff q_buff = {1,""};
            strcpy(q_buff.mtext, longest_word);

            if (msgsnd(q_id, (struct msgbuf *) &q_buff, strlen(q_buff.mtext) + 1, 0) == -1) {
                free(longest_word);
                for (size_t i = 0; i < number_of_words; i++) {
                    if (words_array[i] != NULL)
                        free(words_array[i]);
                }
                free(words_array);
                free(string_of_words);
                exit(EXIT_FAILURE);
            }

            free(longest_word);
            for (size_t i = 0; i < number_of_words; i++) {
                if (words_array[i] != NULL)
                    free(words_array[i]);
            }
            free(words_array);
            free(string_of_words);
            exit(EXIT_SUCCESS);
        }
    }

    for (size_t i = 0; i < number_of_procs; ++i) {
        if (waitpid(pids[i], &status, 0) != pids[i]) {
            for (size_t j = 0; j < number_of_words; j++) {
                if (words_array[j] != NULL)
                    free(words_array[j]);
            }
            free(words_array);
            free(string_of_words);
            return NULL;
        }
    }

    char *longest_word = (char *) malloc(BUFF_SIZE * sizeof(char));
    size_t max_len = 0;

    for (size_t i = 0; i < number_of_procs; ++i) {
        message_buff q_buff;

        if (msgrcv(q_id, (struct msgbuf *) &q_buff, BUFF_SIZE, 1, 0) == -1) {
            for (size_t j = 0; j < number_of_words; j++) {
                if (words_array[j] != NULL)
                    free(words_array[j]);
            }
            free(words_array);
            free(string_of_words);
            return NULL;
        }

        if (q_buff.mtext[0] == '\0') {
            for (size_t j = 0; j < number_of_words; j++) {
                if (words_array[j] != NULL)
                    free(words_array[j]);
            }
            free(words_array);
            free(string_of_words);
            return NULL;
        }

        if (max_len <= strlen(q_buff.mtext)) {
            free(longest_word);
            longest_word = (char *) malloc(BUFF_SIZE * sizeof(char));

            if (longest_word == NULL) {
                for (size_t j = 0; j < number_of_words; j++) {
                    if (words_array[j] != NULL)
                        free(words_array[j]);
                }
                free(words_array);
                free(string_of_words);
                return NULL;
            }

            strcpy(longest_word, q_buff.mtext);
            max_len = strlen(q_buff.mtext);
        }
    }

    for (size_t i = 0; i < number_of_words; i++) {
        if (words_array[i] != NULL)
            free(words_array[i]);
    }
    free(words_array);

    return longest_word;
}


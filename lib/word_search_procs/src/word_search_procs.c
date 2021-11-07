#include "word_search_interface.h"


typedef struct {
    long mtype;
    char mtext[BUFF_SIZE];
} message_buff;


void child_procs_work(char *string_of_words, size_t current_procs_numb, size_t number_of_procs, int q_id) {
    char *longest_word = (char *) calloc(BUFF_SIZE, sizeof(char));
    if (longest_word == NULL) {
        exit(EXIT_FAILURE);
    }
    char *current_word = (char *) calloc(BUFF_SIZE, sizeof(char));
    if (current_word == NULL) {
        free(longest_word);
        exit(EXIT_FAILURE);
    }

    size_t part_size = strlen(string_of_words) / number_of_procs;
    size_t right_border = 0;
    if (current_procs_numb != number_of_procs - 1) {
        right_border = (current_procs_numb + 1) * part_size;
    } else {
        right_border = strlen(string_of_words);
    }

    size_t j = current_procs_numb * part_size;
    size_t skipped_letters_of_word_on_border = 0;
    if (j != 0) {
        while (string_of_words[j] != ' ') {
            j++;
            skipped_letters_of_word_on_border++;
        }
        j++;
        skipped_letters_of_word_on_border++;
    }

    if (current_procs_numb == number_of_procs - 1) {
        skipped_letters_of_word_on_border = 0;
    }
    size_t i = 0;
    while (j < right_border + skipped_letters_of_word_on_border) {
        while (string_of_words[j] != ' ' && string_of_words[j] != '\0') {
            current_word[i] = string_of_words[j];
            i++;
            j++;
        }
        current_word[i] = '\0';
        i = 0;
        j++;
        if (strlen(current_word) > strlen(longest_word)) {
            strcpy(longest_word, current_word);
        }
    }

    message_buff q_buff = {1, ""};
    strcpy(q_buff.mtext, longest_word);

    if (msgsnd(q_id, (struct msgbuf *) &q_buff, strlen(q_buff.mtext) + 1, 0) == -1) {
        free(longest_word);
        free(current_word);
        free(string_of_words);
        exit(EXIT_FAILURE);
    }

    free(string_of_words);
    free(current_word);
    free(longest_word);
    exit(EXIT_SUCCESS);
}


char *find_longest_word(char *string_of_words) {
    if (string_of_words == NULL) {
        return NULL;
    }

    size_t number_of_procs = sysconf(_SC_NPROCESSORS_ONLN);
    int status = 0;

    key_t key = IPC_PRIVATE;
    int q_id = msgget(key, 0660 | IPC_CREAT);

    pid_t pids[number_of_procs];
    for (size_t k = 0; k < number_of_procs; ++k) {
        pids[k] = fork();
        if (pids[k] == 0) {
            child_procs_work(string_of_words, k, number_of_procs, q_id);
        }
    }

    for (size_t i = 0; i < number_of_procs; ++i) {
        if (waitpid(pids[i], &status, 0) != pids[i]) {
            return NULL;
        }
    }

    char *longest_word = (char *) malloc(BUFF_SIZE * sizeof(char));
    size_t max_len = 0;

    for (size_t i = 0; i < number_of_procs; ++i) {
        message_buff q_buff;

        if (msgrcv(q_id, (struct msgbuf *) &q_buff, BUFF_SIZE, 1, 0) == -1) {
            free(string_of_words);
            return NULL;
        }

        if (q_buff.mtext[0] == '\0') {
            return NULL;
        }

        if (max_len <= strlen(q_buff.mtext)) {
            free(longest_word);
            longest_word = (char *) malloc(BUFF_SIZE * sizeof(char));

            if (longest_word == NULL) {
                free(string_of_words);
                return NULL;
            }

            strcpy(longest_word, q_buff.mtext);
            max_len = strlen(q_buff.mtext);
        }
    }
    return longest_word;
}

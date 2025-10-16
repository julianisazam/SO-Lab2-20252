#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "vector.h"

void showError ();

int main (int argc, char* argv[]){
    FILE* input_file = NULL;
    for (int i = 1; i < argc; i++){
        FILE* cur_file = fopen(argv[i], "r");
        if (cur_file == NULL){
            showError();
            exit(1);
        }
    }

    while (1){
        if (input_file == NULL) printf("wish> ");
        char* line = NULL;
        size_t n = 0;
        int len = getline(&line, &n, stdin);
        if (len == -1){
            if (input_file == NULL) continue;
            break;
        }

        free(line);
    }
    
}

int execute_command (Vector tokens) {
    char* command = get(&tokens, 0);
    if (strcmp(command, "exit") == 0) {
        if (tokens.size != 1) showError();
        else exit(0);
        return -1;
    }
    if (
        strcmp(command, "cd") == 0
    ) {
        if (tokens.size != 2) showError();
        else chdir(get(&tokens, 1));
        return -1;
    }
    if (tokens.size >= 1 && strcmp("path", command) == 0) {
        Vector params = create_vector();
        for (int i = 1; i < tokens.size; i++) push_back(&params, get(&tokens, i));
        PATH = params;
        return -1;
    }
}

void showError () {
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
}

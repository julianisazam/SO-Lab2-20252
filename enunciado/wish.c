#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>




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

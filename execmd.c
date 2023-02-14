#include "main.h"

void execmd(int argc, char **argv){
    char *command = NULL;
    if (argv != NULL){
      command = getpath(argc, argv[0]);
      printf("%s\n", command); 
        if (execve("bin/ls", argv, NULL) == -1){
            perror("Error");
        };
    }

    free(command);
}
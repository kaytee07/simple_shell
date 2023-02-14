#include "main.h"


char *remove_trailing_newline(char *str) {
    int length = strcspn(str, "\n");
    memset(str + length, '\0', 1);
    return str;
}

char *getpath(int argc, char *argv) {

    FILE *fp;
    char *path, *command;
    
    if (argc < 2) {
        printf("Usage: which command\n");
        return NULL;
    }

    command = malloc(1024);
    strcpy(command, "which ");
    strcat(command, argv);
    strcat(command, " 2>/dev/null");

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
	free (command);
        return NULL;
    }

    path = malloc(1024); 
    while (fgets(path, 1024, fp) != NULL) {
        printf("%s\n", path);
	free(command);
	return remove_trailing_newline(path);
    }

    pclose(fp);
    free(command);
    return NULL;
}

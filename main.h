#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define DELIM " \n"

void execmd(int argc, char **argv);
char *getpath(int argc, char *argv);

#endif

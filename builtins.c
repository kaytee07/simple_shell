#include "main.h"



int built_in(int argc, char **argv)
{
  if(argc < 0)
    {
      perror("Error: there are no argument");
    }

  if(strcmp(argv[0], "exit") >= 0)
    {
      printf("Exiting the shell...\n");
      exit(0);
    }

  return (-1);
}

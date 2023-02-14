#include "main.h"
 

void env_cmd() {
    char **env = environ;

    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}


int built_in(int argc, char **argv)
{
  if(argc < 0)
    {
      perror("Error: there are no argument");
    }

  if(strcmp(argv[0], "exit") == 0)
    {
      printf("Exiting the shell...\n");
      exit(0);
    }
  else if(strcmp(argv[0], "env") == 0)
    {
      env_cmd();
    }
  else
    {
      return (-1);
    }
    return (1);
}

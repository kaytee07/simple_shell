#include "main.h"

void execmd(int argc, char **argv){
  pid_t pid;
  int status;
  char *command = NULL;
    if (argv != NULL){
      command = getpath(argc, argv[0]);
      pid = fork();
      if (pid == 0)
	{
	  if (execve(command, argv, NULL) == -1)
	    {
            perror("Error");
	    };
	}
      else if (pid > 0)
	{
	  waitpid(pid, &status, 0);
	}
      else
	{
	  perror("Error: fork failed\n");
	}
    }

    free(command);
}

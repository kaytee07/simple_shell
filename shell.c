#include "main.h"

int main(void)
{
  char *prompt = "kaytee$ ", *lineptr = NULL, *lineptr_cpy, **argv, *token;
  int num_of_tokens = 0, i;
  size_t n = 0;
  ssize_t no_chars_read;
  while(1)
    {
      printf("%s", prompt);
      no_chars_read = getline(&lineptr, &n, stdin);
      if(no_chars_read == -1)
	{
	  if (num_of_tokens == 0)
	    {
	      free(lineptr);
	      printf("Exiting shell...\n");
	      return (-1);
	    }
	  else
	    {
	      for (i = 0; argv[i] != NULL; i++)
		{
		  free(argv[i]);
		}
	      free(argv);
	      printf("Exiting shell...\n");
	      return (-1);
	    }
	}
      if(num_of_tokens != 0)
	num_of_tokens = 0;
      lineptr_cpy = malloc(sizeof(lineptr)*no_chars_read);
      if(lineptr_cpy == NULL)
	{
	  free(lineptr);
	  perror("tsh:failure to allocate memory \n");
	  return (-1);
	}
	  strcpy(lineptr_cpy, lineptr);
	  token = strtok(lineptr_cpy, DELIM);
	  while (token != NULL)
	    {
	      num_of_tokens++;
	      token = strtok(NULL, DELIM);
	    }
	  num_of_tokens++;
      argv = malloc(sizeof(char *) * num_of_tokens);
      if(!argv)
	{
	  perror("lsh: failure to allocate memory\n");
	  return (-1);
	}
	  token = strtok(lineptr, DELIM);
      for (i = 0; token != NULL; i++)
	{
	  argv[i] = malloc(strlen(token) + 1);
	  strcpy(argv[i], token);
	  token = strtok(NULL, DELIM);
	}
      argv[i] = NULL;
      
      execmd(num_of_tokens, argv);
      free(lineptr_cpy);
      free(lineptr); 
    }

  return (0);
}

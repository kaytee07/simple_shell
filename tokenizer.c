#include "shell.h"

#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
    int i, j, k, m, numwords = 0;
    char **s;

    // Check for null input string or empty string
    if (str == NULL || str[0] == '\0')
        return NULL;

    // Use a default delimiter if none is provided
    if (!d)
        d = " ";

    // Count the number of words in the input string
    for (i = 0; str[i] != '\0'; i++) {
        if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || str[i + 1] == '\0'))
            numwords++;
    }

    // Return NULL if no words were found
    if (numwords == 0)
        return NULL;

    // Allocate memory for the array of words
    s = malloc((numwords + 1) * sizeof(char *));
    if (!s)
        return NULL;

    // Loop through the input string to extract each word
    for (i = 0, j = 0; j < numwords; j++) {
        // Skip over any leading delimiters
        while (is_delim(str[i], d))
            i++;

        // Find the end of the current word
        k = 0;
        while (!is_delim(str[i + k], d) && str[i + k] != '\0')
            k++;

        // Allocate memory for the current word
        s[j] = malloc((k + 1) * sizeof(char));
        if (!s[j]) {
            // Free memory for previously allocated words and the word array itself
            for (k = 0; k < j; k++)
                free(s[k]);
            free(s);
            return NULL;
        }

        // Copy the current word into the array
        for (m = 0; m < k; m++)
            s[j][m] = str[i++];
        s[j][m] = '\0';
    }

    // Add a null terminator to the end of the array
    s[j] = NULL;
    return s;
}

/**
strtow2 - splits a string into words using a single-character delimiter

@str: the input string

@d: the delimeter character

Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow2(char *str, char d)
{
int i, j, k, m, numwords = 0;
char **s;

if (str == NULL || str[0] == 0)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != d && str[i + 1] == d) ||
(str[i] != d && !str[i + 1]) || str[i + 1] == d)
numwords++;

if (numwords == 0)
return (NULL);

s = malloc((1 + numwords) * sizeof(char *));
if (!s)
return (NULL);

for (i = 0, j = 0; j < numwords; j++)
{
while (str[i] == d && str[i] != d)
i++;

scss
Copy code
 k = 0;
 while (str[i + k] != d && str[i + k] && str[i + k] != d)
 	k++;

 s[j] = malloc((k + 1) * sizeof(char));
 if (!s[j])
 {
 	for (k = 0; k < j; k++)
 		free(s[k]);
 	free(s);
 	return (NULL);
 }

 /* Copy the characters into the new string */
 for (m = 0; m < k; m++)
 	s[j][m] = str[i++];
 s[j][m] = 0;
}

/* Set the last element to NULL */
s[j] = NULL;

return (s);
}

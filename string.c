#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s) // check if string is NULL
		return (0);
	while (*s++) // increment pointer until end of string
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2) // loop until one of the strings ends
	{
		if (*s1 != *s2) // compare characters
			return (*s1 - *s2); // return difference
		s1++;
		s2++;
	}
	if (*s1 == *s2) // both strings are equal
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1); // return negative or positive
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle) // loop until end of needle
		if (*needle++ != *haystack++) // compare characters
			return (NULL); // return NULL if characters don't match
	return ((char *)haystack); // return next character of haystack
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest; // store the start address of dest

	while (*dest) // loop until end of dest
		dest++; // increment pointer
	while (*src) // loop until end of src
		*dest++ = *src++; // copy src to dest
	*dest = *src; // copy null terminator
	return (ret); // return start address of dest
}


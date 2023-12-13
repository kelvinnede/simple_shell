#include "shell.h"

/**
 * bfree - This function frees a pointer and NULLs
 * @ptr: This parameter is the address of the
 * pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

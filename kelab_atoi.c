#include "shell.h"

/**
* interactive - This function returns true
* if shell is interactive mode
* @info: collects address info.
*
* Return: 1 if in an interactive mode, 0 otherwise
*/
int interactive(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - This function checks if character is a delimeter
 * @c: character to check
 * @delim: delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}

/**
 * _isalpha - this function checks for alphabetic character
 * @c: character to input
 * Return: 1 if c is alphabetic, 0 else
 */

int _isalpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}

/**
* _atoi - This function converts a string to an integer
* @s: string to be converted
* Return: 0 if Zero numbers in string, converted number otherwise
*/

int _atoi(char *s)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0; s[i] != '\0' && flag != 2; i++)
{
if (s[i] == '-')
sign *= -1;

if (s[i] >= '0' && s[i] <= '9')
{
flag = 1;
result *= 10;
result += (s[i] - '0');
}
else if (flag == 1)
flag = 2;
}
if (sign == -1)
output = -result;
else
output = result;
return (output);
}

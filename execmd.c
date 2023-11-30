#include "main.h"
/**
 * execmd - This function hadle command prompt execution.
 * @argv: handle the arguments passed by the user.
 */
void execmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;

	if (argv)
	{
		/* get the command */
		command = argv[0];
		/* generate the path to this command before passing it to execve */
		actual_command = get_location(command);

		/* execute the command with execve */
		if (execve(command, argv, NULL) == -1)
		{
			perror("Error:");
		}
	}

}

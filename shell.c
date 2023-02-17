#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - function to create simple shell
 *
 * Return: 0
 */
int main(int argc,char **argv)
{
	char *command = NULL;
	size_t len = 0;
	char *stkn;
	pid_t myPID;
	int status, i;

	while (1)
	{
		printf("$ ");
		getline(&command, &len, stdin);

		stkn = strtok(command, "\n");

		char **arr = malloc(sizeof(char *) * 32);
		arr[0] = stkn;

		i = 1;
		while (stkn != NULL)
		{
			stkn = strtok(NULL, "\n");
			arr[i] = stkn;
			i++;
		}
		if (strcmp(arr[0], "exit") == 0 && (arr[1] == NULL))
			exit(0);
		myPID = fork();
		if (myPID == -1)
		{
			perror("Error");
			return (1);
		}
		else if (myPID == 0)
		{
			if (execve(arr[0], arr,NULL) == -1)
			{
				perror(argv[0]);
				return (1);
			}
		}
		else
		{
			wait(&status);
		}
	}
	free(command);
	return (0);
}

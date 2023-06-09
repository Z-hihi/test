#include "shell.h"

/**
 * _getenv - A function that compares the input value to an environment variable.
 * If the environment variable exists, the result will print out.
 * @name: The passed in variable from the main function.
 * Return: The pointer to the output of the environment variable or
 * returns NULL otherwise.
 */
char *_getenv(const char *name)
{
	int i, j;

	if (name != NULL && name[0] != '\0')
	{
		i = 0;
		while (environ[i] != NULL)
		{
			j = 0;
			while (name[j] == environ[i][j] && name[j] != '\0')
				j++;

			if (name[j] == '\0' && environ[i][j] == '=')
				return (&environ[i][j + 1]);

			i++;
		}
	}
	return (NULL);
}

/**
 * _getPATH - A function that separates each directory of PATH on a newline.
 * @str: A pointer to the value of PATH.
 * @tok_UsInput: The tokenized user input.
 * Return: A double pointer to a string array that stores each directory in the PATH.
 */
char **_getPATH(char *str, char **tok_UsInput)
{
	char *tok_PATH, *tempstr, *fwd_slash, **temp_arr, *PATH_cpy;
	int i, a, BUFSIZE, count;

	i = a = 0;
	BUFSIZE = 1024;
	fwd_slash = "/";
	count = 0;
	while (str[count] != '\0')
		count++;

	PATH_cpy = malloc(sizeof(char) * (count + 1));
	if (PATH_cpy == NULL)
		_exit(1);
	_strcpy(PATH_cpy, str);

	tok_PATH = strtok(PATH_cpy, ":");
	free(PATH_cpy);

	temp_arr = malloc(sizeof(char *) * BUFSIZE);
	if (temp_arr == NULL)
		_exit(1);

	tempstr = malloc(sizeof(char) * BUFSIZE);
	if (tempstr == NULL)
	{
		free(temp_arr);
		_exit(1);
	}

	while (tok_PATH != NULL)
	{
		_strcpy(tempstr, tok_PATH);
		_strcat(tempstr, fwd_slash);
		_strcat(tempstr, tok_UsInput[a]);
		tok_PATH = strtok(NULL, ": ");
		temp_arr[i] = _strdup(tempstr);
		_memset(tempstr, 0, BUFSIZE);
		i++;
	}

	temp_arr[i] = NULL;

	return (temp_arr);
}


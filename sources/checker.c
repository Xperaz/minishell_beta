#include "../includes/minishell.h"

void	ft_check(char *command)
{
	if (!command || !strncmp(command, "exit", 4))
	{
		printf("exit");
		exit (0);
	}
	else if (command[0] != '\0')
		add_history(command);
}

int	command_checker(char *command)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (command[++i])
	{
		if (quotes == 0 && command[i] == '"')
			quotes = 2;
		else if (quotes == 2 && command[i] == '"')
			quotes = 0;
		else if (quotes == 0 && command[i] == '\'')
			quotes = 1;
		else if (quotes == 1 && command[i] == '\'')
			quotes = 0;
		else if (quotes == 0 && (command[i] == '\\' || command[i] == ';'))
			return (printf("%s", "Error"), EXIT_FAILURE);
	}
	if (quotes != 0)
		return (printf("%s\n", "Error"), -1);
	return (0);
}
#include "../includes/minishell.h"

void	print_error()
{
	printf("%s\n", errors);
	rl_on_new_line();
}
void	ft_check(char *command)
{
	if (!strncmp(command, "exit", 4))
	{
		printf("exit");
		exit(1);
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
			print_error();
	}
	if (quotes != 0)
		print_error();
	return (0);
}
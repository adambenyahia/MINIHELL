#include "minishell.h"

int	alpha_string(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i++]));
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (1);
	return (0);
}

int	exit_nbr(char *str)
{
	int	ex;

	ex = ft_atoi(str);
	if (ex < 0)
		return ()
}

void	ft_exit(char **cmd)
{
	if (!cmd[1])
		free_exit(1);
	if (cmd[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (g_spot.exit_status = 1, (void)0);
	}
	if (alpha_string(cmd[1]))
	{
		printf("bash: exit: %s: numeric argument required", cmd[1]);
	}
	free_exit(exit_nbr(cmd[1]));
}
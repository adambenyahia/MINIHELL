#include "minishell.h"

void	ft_echo(char **cmd, int fd)
{
	int i;
	bool nl;

	i = 0;
	nl = true;
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 3))
	{
		i = 1;
		nl = false;
	}
	while (cmd[1 + i])
	{
		ft_putstr_fd(cmd[1 + i], fd);
		i++;
		if (cmd[i + 1])
			ft_putstr_fd(" ", fd);
	}
	if (nl)
		ft_putstr_fd("\n", fd);
	g_spot.exit_status = 0;
}
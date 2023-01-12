/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:57:38 by beadam            #+#    #+#             */
/*   Updated: 2023/01/12 01:19:52 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **cmd, t_env *env)
{
	char	*path;
	char	*tmp;

	path = NULL;
	if (cmd[2])
		return (printf("minishell: cd: too many arguments\n"), (void)0);
	if (!cmd[1] || !cmd[1][0])
	{
		path = find_env("HOME", env);
		if (!path[0])
		{
			g_spot.exit_status = 1;
			printf("minishell: cd"
				" HOME is not set\n");
			return ;
		}
	}
	else if (!ft_strncmp(cmd[1], ".", ft_strlen(cmd[1])))
	{
		path = getcwd(path, __DARWIN_MAXPATHLEN);
		if (!path)
		{
			g_spot.exit_status = 1;
			perror("minishell: cd: error retrieving "
				"current directory \ngetcwd: cannot access parent directories");
			return ;
		}
	}
	else
		path = cmd[1];
	if (chdir(path) < 0)
	{
		tmp = ft_strjoin("cd: ", path);
		perror(tmp);
		g_spot.exit_status = 1;
		free(tmp);
		free(path);
	}
}

void	pwd_cmd(char **cmd, int fd)
{
	char	*path;

	path = NULL;
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
	{
		g_spot.exit_status = 1;
		printf("minishell: pwd: -%c: invalid option\n", cmd[1][1]);
		printf("usage: pwd [with no options]\n");
		return ;
	}
	path = getcwd(path, __DARWIN_MAXPATHLEN);
	ft_putstr_fd(path, fd);
	ft_putstr_fd("\n", fd);
	free(path);
}

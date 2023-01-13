/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:36:23 by beadam            #+#    #+#             */
/*   Updated: 2023/01/13 04:49:01 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getpath(char **cmd, t_env *env, char *path);

void	ft_cd(char **cmd, t_env *env)
{
	char	*path;
	char	*tmp;

	path = NULL;
	if (cmd [1] && cmd[2])
		return (printf("minishell: cd: too many arguments\n"), (void)0);
	path = ft_getpath(cmd, env, path);
	if (!path)
		return ;
	if (chdir(path) < 0)
	{
		tmp = ft_strjoin("cd: ", path);
		perror(tmp);
		g_spot.exit_status = 1;
		free(tmp);
		free(path);
	}
}

char	*ft_getpath(char **cmd, t_env *env, char *path)
{
	if (!cmd[1] || !cmd[1][0])
	{
		path = find_env("HOME", env);
		if (!path[0])
		{
			g_spot.exit_status = 1;
			printf("minishell: cd"
				" HOME is not set\n");
			return (NULL);
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
			return (NULL);
		}
	}
	else
		path = cmd[1];
	return (path);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 04:09:53 by beadam            #+#    #+#             */
/*   Updated: 2023/01/08 04:10:01 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_slash(char *str)
{
	if (!str)
		return (ft_strdup("/"));
	return (ft_strjoin(str, "/"));
}

char	*cmd_path(char *cmd, t_env *env)
{
	char	**path;
	char	*var;
	int		i;

	if (!cmd || !*cmd || !env)
		return (NULL);
	if (!access(cmd, X_OK | F_OK))
		return (cmd);
	i = 0;
	var = find_env("PATH", env);
	path = ft_split(var, ':');
	while (path[i])
	{
		path[i] = append_slash(path[i]);
		path[i] = ft_strjoin(path[i], cmd);
		if (!access(path[i], X_OK))
			return (path[i]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 04:09:53 by beadam            #+#    #+#             */
/*   Updated: 2023/01/13 01:04:05 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_slash(char *str)
{
	point(str);
	if (!str)
		return (point(ft_strdup("/")));
	return (point(ft_strjoin(str, "/")));
}

char	*cmd_path(char *cmd, t_env *env)
{
	char	**path;
	char	*var;
	int		i;

	if (!cmd || !*cmd || !env)
		return (NULL);
	if ((cmd[0] == '.' || cmd[0] == '/'))
		if (access(cmd, X_OK | F_OK))
			return (NULL);
	if (!access(cmd, X_OK | F_OK))
		return (cmd);
	i = 0;
	var = find_env("PATH", env);
	path = point(ft_split(var, ':'));
	while (path[i])
	{
		path[i] = append_slash(path[i]);
		path[i] = point(ft_strjoin(path[i], cmd));
		if (!access(path[i], X_OK))
			return (path[i]);
		i++;
	}
	return (NULL);
}

char	**cmdstring(t_tree *node)
{
	t_cmdlist	*cmdlist;
	int			i;
	char		**cmdstring;

	cmdstring = point(malloc(sizeof(char *) * (node->cmdlen + 1)));
	if (!cmdstring)
		return (NULL);
	cmdlist = node->cmdlist;
	i = 0;
	while (cmdlist)
	{
		cmdstring[i] = cmdlist->cmd;
		cmdlist = cmdlist->next;
		i++;
	}
	cmdstring[i] = NULL;
	return (cmdstring);
}

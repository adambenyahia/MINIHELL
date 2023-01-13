/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export++.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 05:05:29 by beadam            #+#    #+#             */
/*   Updated: 2023/01/13 05:21:40 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_export(char *cmd, int pos, int size)
{
	char	**args;

	args = point((char **)malloc(sizeof(char *) * 2));
	if (!args)
		return (NULL);
	args[0] = point(ft_substr(cmd, 0, pos));
	args[1] = point(ft_strdup(cmd + pos + size));
	return (args);
}

t_key_value	*ft_create_node(char **args)
{
	t_key_value	*node;

	node = point(malloc(sizeof(t_key_value)));
	node->next = NULL;
	node->key = args[0];
	node->value = args[1];
	return (node);
}

void	ft_append_var(char **args, t_env **env)
{
	t_key_value	*node;

	if ((*env)->size == 0)
		ft_add_var(args, env);
	else
	{
		node = find_env2(args[0], *env);
		if (!node)
		{
			ft_add_var(args, env);
		}
		else
			node->value = point(ft_strjoin(node->value, args[1]));
	}
}

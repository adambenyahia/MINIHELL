/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:25:09 by beadam            #+#    #+#             */
/*   Updated: 2023/01/11 10:43:54 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **cmd, t_env **env)
{
	int	i;

	i = 0;
	while (cmd[++i])
		remove_env(cmd[i], env);
	g_spot.exit_status = 0;
}

void	remove_env(char *tf, t_env **env)
{
	t_key_value	**node;
	t_key_value	*save;

	node = &(*env)->head;
	save = *node;
	if (!ft_strncmp(tf, (*node)->value, MAXNAMLEN))
	{
		(*env)->head = ((*env)->size--, (*node)->next);
	}
	while (*node)
	{
		if ((*node)->next && !ft_strncmp(tf, (*node)->next->key, MAXNAMLEN))
		{
			(*node)->next = ((*env)->size--, (*node)->next->next);
		}
		*node = (*node)->next;
	}
	*node = save;
}

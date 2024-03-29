/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:56:15 by beadam            #+#    #+#             */
/*   Updated: 2023/01/12 09:04:54 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_key_value	*key_retreave(char *c)
{
	size_t		len;
	t_key_value	*node;

	node = point(malloc(sizeof(t_key_value)));
	node->next = NULL;
	len = 0;
	while (c[len] && c[len] != '=')
		len++;
	if (!len)
		return (NULL);
	node->key = point(ft_substr(c, 0, len));
	node->value = point(ft_strdup(c + len + 1));
	return (node);
}

t_env	*init_env(char **env)
{
	t_env	*list;

	list = point(malloc(sizeof(t_env)));
	list->size = string_table_len(env);
	list->head = NULL;
	list->tail = NULL;
	list->tab = env;
	while (*env)
	{
		if (!list->head)
		{
			list->head = key_retreave(*env);
			list->tail = list->head;
			continue ;
		}
		list->tail->next = key_retreave(*env);
		list->tail = list->tail->next;
		env++;
	}
	return (list);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_list_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:50 by beadam            #+#    #+#             */
/*   Updated: 2023/01/13 05:09:13 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens	*ft_lstend(t_tokens *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_tokens	*lastdel_dll(t_tokens **token)
{
	t_tokens	*node;
	t_tokens	*lst;

	lst = ft_lstend(*token);
	node = lst;
	lst = lst->previous;
	if (lst)
		lst->next = NULL;
	return (node);
}

t_tokens	*shift_node(t_tokens **dll, t_tokens *node)
{
	if (!node->next && !node->previous)
	{
		*dll = NULL;
		return (node);
	}
	else if (!node->previous)
	{
		*dll = (*dll)->next;
		return (node);
	}
	else if (!node->next)
		return (lastdel_dll(dll));
	node->previous->next = node->next;
	node->next->previous = node->previous;
	return (node);
}

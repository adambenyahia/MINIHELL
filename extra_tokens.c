/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:57:34 by beadam            #+#    #+#             */
/*   Updated: 2023/01/08 04:22:31 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(t_tokens **tokens)
{
	t_tokens	*node;

	node = *tokens;
	while (node)
	{
		if (node->flag == SQ || node->flag == DQ)
		{
			if (!node->next || node->next->flag != node->flag)
			{
				node_del_dll(tokens, node);
				node = *tokens;
				continue ;
			}
			else
			{
				node->flag = WORD;
				node->token = ft_strdup("");
				continue ;
			}
		}
		node = node->next;
	}
}

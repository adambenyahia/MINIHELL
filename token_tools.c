/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:48 by beadam            #+#    #+#             */
/*   Updated: 2023/01/07 00:24:49 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	if_token(char c)
{
	return (c != '|' && c != ' ' && c != '\'' && c != '$' && c != '>'
		&& c != '<' && c != '"');
}

static t_tokens	*new_token(char *token, int flag)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		printf("not allocated\n");
	new->token = ft_strdup(token);
	new->flag = flag;
	new->next = NULL;
	new->tail = NULL;
	new->previous = NULL;
	return (new);
}
static void	add_token(t_tokens **list, t_tokens *new)
{
	if (!list || !(*list))
	{
		*list = new;
		(*list)->tail = *list;
		return ;
	}
	(*list)->tail->next = new;
	new->previous = (*list)->tail;
	(*list)->tail = new;
}
int	set_token(t_tokens **list, char *input, int len, int flag)
{
	int i;

	i = 0;
	if (!len)
		return (0);
	if (flag == SP)
	{
		while (input[i] && input[i] == ' ' && input[i + 1] == ' ')
			i++;
		add_token(list, new_token("SPACE", SP));
		return (i + 1);
	}
	add_token(list, new_token(ft_substr(input, 0, len), flag));
	return (len);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:59 by beadam            #+#    #+#             */
/*   Updated: 2023/01/12 23:30:20 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*parce_please(t_tokens **head)
{
	t_tree	*tree;

	if (!*head || !head)
		return (NULL);
	tree = commander(head);
	if (!tree)
		return (NULL);
	while (*head && (*head)->flag == PIPE)
	{
		*head = (*head)->next;
		tree = plant_tree(PIPE, NULL, tree, commander(head));
		tree = water_tree(tree, NULL, 1, 0);
		if (!tree->right)
			return (NULL);
	}
	return (tree);
}

t_tree	*commander(t_tokens **token)
{
	t_cmdlist	*list;
	t_io_fd		io;
	int			err;
	int			parced;
	size_t		cmdlen;

	if (!*token)
		return (NULL);
	err = 0;
	init_variables(&parced, &io, &list, &cmdlen);
	while (*token && (*token)->flag != PIPE)
	{
		err = cmd_lister(token, &io, &list, &cmdlen);
		parced = 1;
		if (err != 0)
			break ;
		*token = (*token)->next;
	}
	if (parced == 0)
		return (NULL);
	return (water_tree(plant_tree(CMD, &io, NULL, NULL), list, cmdlen, err));
}

int	cmd_lister(t_tokens **token, t_io_fd *io, t_cmdlist **list, size_t *cmdlen)
{
	int	error;

	error = 0;
	if ((*token)->flag == OUTRED || (*token)->flag == APPEND)
		error = set_fd(&(io->out), STDOUT_FILENO, token);
	else if ((*token)->flag == INRED)
		error = set_fd(&(io->in), STDIN_FILENO, token);
	else if ((*token)->flag == HERDOC)
		error = heredoc(token, &(io->in));
	else
		error = cmd_addback(list, (*token)->token, cmdlen);
	return (error);
}

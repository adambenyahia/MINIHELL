/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:25:00 by beadam            #+#    #+#             */
/*   Updated: 2023/01/13 00:12:05 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_addback(t_cmdlist **head, char *cmd, size_t *cmdlen)
{
	t_cmdlist	*new;
	t_cmdlist	*tmp;

	new = point(malloc(sizeof(t_cmdlist)));
	new->cmd = cmd;
	new->next = NULL;
	(*cmdlen)++;
	if (!head || !*head)
		return (*head = new, 0);
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

void	init_variables(int *v, t_io_fd *io, t_cmdlist **cmdlist,
		size_t *cmdlen)
{
	*v = 0;
	*cmdlen = 0;
	io->in = STDIN_FILENO;
	io->out = STDOUT_FILENO;
	*cmdlist = NULL;
}

t_tree	*plant_tree(int type, t_io_fd *io,
		t_tree *left, t_tree *right)
{
	t_tree	*chajara;

	chajara = point(malloc(sizeof(t_tree)));
	if (!chajara)
		return (NULL);
	chajara->left = left;
	chajara->right = right;
	chajara->type = type;
	if (type == PIPE)
	{
		chajara->file.in = STDIN_FILENO;
		chajara->file.out = STDOUT_FILENO;
	}
	else
	{
		chajara->file.in = io->in;
		chajara->file.out = io->out;
	}
	return (chajara);
}

t_tree	*water_tree(t_tree *chajara, t_cmdlist *cmd,
			size_t cmdlen, int err)
{
	if (!chajara)
		return (NULL);
	chajara->cmdlist = cmd;
	chajara->err = err;
	chajara->cmdlen = cmdlen;
	return (chajara);
}

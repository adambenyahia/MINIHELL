/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:25:00 by beadam            #+#    #+#             */
/*   Updated: 2023/01/07 00:25:01 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_addback(t_cmdlist **head, char *cmd, size_t *cmdlen)
{
	t_cmdlist	*new;
	t_cmdlist	*tmp;

	new = malloc(sizeof(t_cmdlist));
	if (!new)
		return (80085);
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

void	init_variables(int *e, int *v, io_fd *io, t_cmdlist **cmdlist,
		size_t *cmdlen)
{
	*e = 0;
	*v = 0;
	*cmdlen = 0;
	io->in = STDIN_FILENO;
	io->out = STDOUT_FILENO;
	*cmdlist = NULL;
}

t_tree	*tree_gen(int type, t_cmdlist *cmd, size_t cmdlen, io_fd *io, int err,
		t_tree *left, t_tree *right)
{
	t_tree *chajara;

	chajara = malloc(sizeof(t_tree));
	if (!chajara)
		return (NULL);
	chajara->left = left;
	chajara->right = right;
	chajara->type = type;
	chajara->cmdlist = cmd;
	chajara->errorflag = err;
	chajara->cmdlen = cmdlen;
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
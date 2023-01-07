/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:25:02 by beadam            #+#    #+#             */
/*   Updated: 2023/01/07 05:53:31 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fd(int *io, int def, t_tokens **token)
{
	int	flags;

	if (!*token || !(*token)->next || (*token)->next->flag != WORD)
	{
		if (!(*token)->next)
			printf("minishell: syntax error near unexpected token `newline'\n");
		else if ((*token)->next->flag != WORD)
			printf("minishell: syntax error near unexpected token \'%s\'\n",
					(*token)->next->token);
		return (*io = -1, -2);
	}
	if (*io != def)
		close(*io);
	if ((*token)->flag == INRED)
		flags = O_RDONLY;
	else if ((*token)->flag == OUTRED)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		flags = O_CREAT | O_WRONLY | O_APPEND;
	*token = (*token)->next;
	*io = open((*token)->token, flags, 0666);
	if (*io == -1)
		return (errno);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	heredoc(t_tokens **head, int *io)
{
	char	*input;
	int		fd[2];

	*head = (*head)->next;
	if (!*head || !(*head)->token)
		return (printf("minishell: syntax error near unexpected token `newline'\n"),
				-2);
	if ((*head)->flag != WORD)
		return (printf("minishell: syntax error near unexpected token `%s'\n",
				(*head)->token), -2);
	if (pipe(fd) == -1)
		return (*io = -1, errno);
	while (1209)
	{
		input = readline("heredoc>");
		if (!input)
			return (*io = -1, -1);
		if (!ft_strcmp(input, (*head)->token))
			break ;
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
	close(fd[1]);
	return (*io = fd[0], 0);
}

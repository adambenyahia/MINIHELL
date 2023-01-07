/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_calibration.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:54 by beadam            #+#    #+#             */
/*   Updated: 2023/01/07 00:24:55 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_syntax(t_tokens **head)
{
	char	*c;
	int		len;
	int		i;

	i = 0;
	if (g_spot.quotes & BAD)
		g_spot.quotes ^= BAD;
	while ((g_spot.quotes & DOUBLE) || (g_spot.quotes & SINGLE))
	{
		while (g_spot.quotes & DOUBLE)
		{
			i = 0;
			c = readline("DQUOTE> ");
			len = ft_strlen(c);
			if (!c)
			{
				printf("\nminishell: unexpected EOF while looking for matching `\"'\n");
				return (1);
			}
			while (*c)
			{
				c += set_word_token(head, c);
				if (*c == '"')
					c += get_double_quote(head, c);
				if (*c == '\'')
					c += get_single_quote(head, c);
			}
			// free(c);
		}
		while (g_spot.quotes & SINGLE)
		{
			i = 0;
			c = readline("SQUOTE> ");
			len = ft_strlen(c);
			if (!c)
			{
				printf("\nminishell: unexpected EOF while looking for matching `\"'\n");
				return (1);
			}
			while (*c)
			{
				c += set_word_token(head, c);
				if (*c == '\'')
					c += get_single_quote(head, c);
				if (*c == '"')
					c += get_double_quote(head, c);
			}
			// free(c);
		}
	}
	return (0);
}

int	quotes(t_tokens **head)
{
	int i;
	char *c;
	char *sub_cmd;
	char quo[2];

	(void)head;
	sub_cmd = ft_strdup("");
	while (g_spot.quotes & DOUBLE || g_spot.quotes & SINGLE)
	{
		i = 0;
		if (g_spot.quotes & DOUBLE)
			quo[0] = '"';
		if (g_spot.quotes & SINGLE)
			quo[0] = '\'';
		quo[1] = '\0';

		c = readline(g_spot.quotes & DOUBLE ? "DQUOTE >" : "SQUOTE >");
		while (c[i])
		{
			if (c[i] == '"' && g_spot.quotes ^ SINGLE)
				g_spot.quotes ^= DOUBLE;
			if (c[i] == '\'' && g_spot.quotes ^ DOUBLE)
				g_spot.quotes ^= SINGLE;
			i++;
		}
		sub_cmd = ft_strjoin(sub_cmd, ft_strjoin(quo, c));
	}
	// ft_token(head,sub_cmd);
	return (0);
}
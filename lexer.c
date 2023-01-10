/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:25:07 by beadam            #+#    #+#             */
/*   Updated: 2023/01/10 05:36:59 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fixquotes(void)
{
	char	*c;
	char	*tmp;

	c = NULL;
	tmp = c;
	if (g_spot.quotes & DOUBLE)
	{
		c = readline("DQUOTE>");
		c = ft_strjoin("\n", c);
	}
	else if (g_spot.quotes & SINGLE)
	{
		c = readline("SQUOTE>");
		c = ft_strjoin("\n", c);
	}
	else if (g_spot.quotes & EPI)
	{
		c = readline("pipe>");
		if (c[0])
			g_spot.quotes ^= EPI;
	}
	if (!c)
		return (g_spot.exit_status = 130,NULL);
	free(tmp);
	return (c);
}

char	*lexicon(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (NULL);
	while (c[i] && (c[i] == ' ' || c[i] == '\t'))
		i++;
	if (c[i] == '|' && g_spot.quotes ^ SINGLE && g_spot.quotes ^ DOUBLE)
		return (printf("minishell: syntax error near unexpected token `|'\n"),
			NULL);
	while (c[i])
	{
		if (c[i] == '"' && g_spot.quotes ^ SINGLE)
			g_spot.quotes ^= DOUBLE;
		if (c[i] == '\'' && g_spot.quotes ^ DOUBLE)
			g_spot.quotes ^= SINGLE;
		if (c[i++] == '|' && (g_spot.quotes ^ SINGLE && g_spot.quotes ^ DOUBLE))
		{
			while (c[i] && (c[i] == ' ' || c[i] == '\t'))
				i++;
			if (!c[i])
				g_spot.quotes ^= EPI;
		}
		i++;
	}
	return (c);
}

char	*lexer(char *c)
{
	int		in;
	char	*tmp;

	in = 1;
	if (!c)
	{
		printf("EOF\n");
		exit(0);
	}
	g_spot.quotes = INITQ;
	lexicon(c);
	while (g_spot.quotes && in)
	{
		tmp = fixquotes();
		if (!tmp)
			return (NULL);
		c = ft_strjoin(c, lexicon(tmp));
		free(tmp);
		if (!c)
			in = 0;
	}
	return (c);
}

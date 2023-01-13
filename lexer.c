/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:25:07 by beadam            #+#    #+#             */
/*   Updated: 2023/01/13 04:53:59 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fixquotes(void)
{
	char	*c;
	char	*tmp;

	tmp = NULL;
	c = NULL;
	if (g_spot.quotes & DOUBLE)
	{
		tmp = readline("DQUOTE>");
		c = ft_strjoin("\n", tmp);
	}
	else if (g_spot.quotes & SINGLE)
	{
		tmp = readline("SQUOTE>");
		c = ft_strjoin("\n", tmp);
	}
	else if (g_spot.quotes & EPI)
	{
		c = readline("pipe>");
		if (c[0])
			g_spot.quotes ^= EPI;
	}
	free(tmp);
	if (!c)
		return (g_spot.exit_status = 130, NULL);
	return (c);
}

static void	ft_quotes(char *c, int i)
{
	while (c[i])
	{
		if (c[i] == '"' && g_spot.quotes ^ SINGLE)
			g_spot.quotes ^= DOUBLE;
		else if (c[i] == '\'' && g_spot.quotes ^ DOUBLE)
			g_spot.quotes ^= SINGLE;
		else if (c[i] == '|' && \
			(g_spot.quotes ^ SINGLE && g_spot.quotes ^ DOUBLE))
		{
			i++;
			while (c[i] && (c[i] == ' ' || c[i] == '\t'))
				i++;
			if (!c[i])
				g_spot.quotes ^= EPI;
		}
		i++;
	}	
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
	ft_quotes(c, i);
	return (c);
}

char	*lexer(char *c)
{
	int		in;
	char	*tmp;

	in = 1;
	if (!c)
		free_exit(0);
	g_spot.quotes = INITQ;
	point(lexicon(c));
	while (g_spot.quotes && in)
	{
		tmp = fixquotes();
		if (!tmp)
			return (NULL);
		c = point(ft_strjoin(c, lexicon(tmp)));
		if (!c)
			in = 0;
		free(tmp);
	}
	return (c);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:59:35 by beadam            #+#    #+#             */
/*   Updated: 2021/11/10 22:59:38 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_counter(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && c != str[i])
			i++;
		while (c && c == str[i])
			i++;
		count++;
	}
	return (count);
}

static int	word_counter(char *str, char c)
{
	int	count;

	count = 0;
	while (*str && c != *str)
	{
		count++;
		str++;
	}
	return (count);
}

static char	*create_word(char *str, char c, char **word)
{
	int	wcount;
	int	j;

	wcount = word_counter(str, c);
	*word = malloc(sizeof(char) * (wcount + 1));
	if (*word == 0)
		return (0);
	(*word)[wcount] = 0;
	j = 0;
	while (j < wcount)
		(*word)[j++] = *str++;
	while (c && c == *str)
		str++;
	return (str);
}

static void	free_split(char **result, int size)
{
	while (size--)
	{
		free(result[size]);
	}
	free(result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		spcount;
	int		i;

	if (s == 0)
		return (0);
	while (c && *s && c == *s)
		s++;
	spcount = split_counter((char *)s, c);
	result = malloc(sizeof(char *) * (spcount + 1));
	if (!result)
		return (0);
	result[spcount] = 0;
	i = 0;
	while (i < spcount)
	{
		s = create_word((char *)s, c, result + i);
		if (s == 0)
		{
			free_split(result, i);
			return (0);
		}
		i++;
	}
	return (result);
}

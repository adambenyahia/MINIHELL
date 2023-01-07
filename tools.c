/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:40 by beadam            #+#    #+#             */
/*   Updated: 2023/01/07 00:24:41 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

bool	isword(int c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int	spaces_only(char *input)
{
	while (*input)
		if(!ft_isspace(*input++)) // inpliment :ft_isspace:
			return (0);
	return (1);
}

size_t string_table_len(char **c)
{
	size_t i = 0;

	while (c[i])
		i++;
	return i;
}

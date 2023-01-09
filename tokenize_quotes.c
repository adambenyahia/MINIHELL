/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:42 by beadam            #+#    #+#             */
/*   Updated: 2023/01/09 01:04:02 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_single_quote(t_tokens **head, char *input)
{
	int	i;

	i = 0;
	if (*input == '\'' && *(input + 1) == '\'')
		return (set_token(head, "", 1, WORD), 2);
	input++;
	while (input[i] && input[i] != '\'')
		i++;
	set_token(head, input, i, WORD);
	input += i;
	i++;
	return (i + 1);
}

int	get_double_quote(t_tokens **head, char *input)
{
	int	i;
	int	v;
	int	tmp;

	tmp = 1;
	i = 0;
	if (*input == '"' && *(input + 1) == '"')
		return (set_token(head, "", 1, WORD), 2);
	input++;
	while (input[i] && input[i] != '"')
	{
		if (input[i] == '$' && isword(input[i + 1]))
		{
			input += set_token(head, input, i, WORD);
			v = tokenize_variables(head, input);
			input += v;
			tmp += v;
			i = 0;
			continue ;
		}
		i++;
		tmp++;
	}
	input += set_token(head, input, i, WORD);
	return (tmp);
}

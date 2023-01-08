/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:45 by beadam            #+#    #+#             */
/*   Updated: 2023/01/08 07:48:49 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token(t_tokens **head, char *line)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(line);
	while (*line && i < len)
	{
		if (*line == '|')
			i = set_token(head, line, 1, PIPE);
		else if (*line == ' ')
			i = set_token(head, line, 1, SP);
		else if (*line == '\'')
			i = get_single_quote(head, line);
		else if (*line == '"')
			i = get_double_quote(head, line);
		else if (*line == '>' && *(line + 1) != '>')
			i = set_token(head, line, 1, OUTRED);
		else if (*line == '>' && *(line + 1) == '>')
			i = set_token(head, line, 2, APPEND);
		else if (*line == '<' && *(line + 1) != '<')
			i = set_token(head, line, 1, INRED);
		else if (*line == '<' && *(line + 1) == '<')
			i = set_token(head, line, 2, HERDOC);
		else if (*line == '$' && (ft_isalnum(*(line + 1)) || *(line + 1) == '_'
				|| *(line + 1) == '?' || *(line + 1) == '0' || *(line
					+ 1) == '$'))
			i = tokenize_variables(head, line);
		else
			i = set_word_token(head, line);
		line += i;
	}
}

int	set_word_token(t_tokens **list, char *input)
{
	int	i;

	i = 0;
	if (*input == '$')
		return (set_token(list, input, 1, WORD));
	while (input[i] && if_token(input[i]))
		i++;
	set_token(list, input, i, WORD);
	return (i);
}

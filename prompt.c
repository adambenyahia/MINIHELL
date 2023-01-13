/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:56 by beadam            #+#    #+#             */
/*   Updated: 2023/01/12 23:15:45 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*lexer(char *c);

t_tokens	*prompt(void)
{
	char		*input;
	t_tokens	*token;

	token = NULL;
	input = lexer(readline("minishell $ "));
	if (!input)
		return (NULL);
	add_history(input);
	if (spaces_only(input))
		return (NULL);
	ft_token(&token, input);
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:56 by beadam            #+#    #+#             */
/*   Updated: 2023/01/12 01:25:08 by beadam           ###   ########.fr       */
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
	// if (!ft_strncmp("exit", input, 4))
	// 	exit(0);
	if (!spaces_only(input))
		add_history(input);
	else
		return (free(input), NULL);
	ft_token(&token, input);
	return (free(input), token);
}

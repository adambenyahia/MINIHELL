/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:35 by beadam            #+#    #+#             */
/*   Updated: 2023/01/07 01:04:40 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_variables(t_tokens **head, char *input)
{
	int i;

	i = 1;
	if (ft_isdigit(*(input + 1)) && *input + 1 != '0')
		return 2;
	if (*(input + 1) == '?' || *(input + 1) == '0' || *(input + 1) == '$')
		return (set_token(head, input, 2, VAR) + 1);
	while (input[i] && isword(input[i]))
		i++;
	if (i == 1)
	{
		set_token(head, input, 1, WORD);
		return (1);
	}
	set_token(head, input , i, VAR);
	return (i);
}
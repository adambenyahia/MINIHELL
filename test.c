/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:52 by beadam            #+#    #+#             */
/*   Updated: 2023/01/07 00:24:53 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env_list_test(t_env *env_list)
{
	while (env_list->head)
	{
		printf("%s=%s\n", env_list->head->key, env_list->head->value);
		env_list->head = env_list->head->next;
	}
	fflush(stdout);
}

void token_list_test(t_tokens *token_list)
{
	char l[20][20] = {"PIPE",
				"OUTR",
				"APND",
				"INR",
				"HERD",
				"SQ",
				"DQ",
				"VAR",
				"WORD",
				"SP",
				"out of range"};
	int i = 0;
	execv("clear",NULL);
	printf("\tFLAG\t\t\tTOKEN\n");
	if (!token_list)
	{
		printf("Empty\n");
		return;
	}
	while (token_list)
	{
		printf("%d:\t%s\t\t\t%s\n", i++, l[token_list->flag], token_list->token);
		token_list = token_list->next;
	}
}

void	display_cmd_string(char **str)
{
	int i;

	i = 0;
    printf("CMDS::::\n");
	while (str[i])
	{
		printf("%d: %s\n", i, str[i]);
		i++;
	}
    printf("\n");
}
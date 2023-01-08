/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:25:05 by beadam            #+#    #+#             */
/*   Updated: 2023/01/08 07:52:18 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_spot;

int	main(int argc, char const *argv[], char **env)
{
	t_env		*lst_env;
	t_tokens	*token;
	t_tree		*tree;

	(void)argc;
	(void)argv;
	tree = NULL;
	lst_env = init_env(env);
	sig_handler();
	while (true)
	{
		token = prompt();
		expand(lst_env, &token);
		tree = parce_please(&token);
		exec(tree, &lst_env);
		free(token);
	}
	return (0);
}

		// token_list_test(token);
		// display_cmd_string(cmdstring(tree));
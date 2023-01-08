/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:25:12 by beadam            #+#    #+#             */
/*   Updated: 2023/01/08 07:37:22 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_env(t_env *env)
{
	t_key_value	*head;

	head = env->head;
	while (head)
	{
		printf("declare -x %s", head->key);
		if (head->value)
			printf("=\"%s\"", head->value);
		printf("\n");
		head = head->next;
	}
}

void	ft_export(char **cmd, t_env **env)
{
	if (!cmd[1])
		return (display_env(*env));
}

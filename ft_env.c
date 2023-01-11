/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:58:17 by beadam            #+#    #+#             */
/*   Updated: 2023/01/11 05:29:48 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **cmd, t_env *env, int fd)
{
	t_key_value	*tmp;

	if (cmd[1])
	{
		printf("usage: env [no options] [no arguments]\n");
		return ;
	}
	tmp = env->head;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->key, fd);
		ft_putchar_fd('=', fd);
		ft_putendl_fd(tmp->value, fd);
		tmp = tmp->next;
	}
}

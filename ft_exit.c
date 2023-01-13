/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 08:55:37 by beadam            #+#    #+#             */
/*   Updated: 2023/01/13 00:30:40 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alpha_string(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i++]))
		;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (1);
	return (0);
}

int	exit_nbr(char *str)
{
	int	ex;

	ex = ft_atoi(str);
	if (ex < 0)
		ex = 256 + (ex % 256);
	else
		ex %= 256;
	g_spot.exit_status = ex;
	return (ex);
}

void	ft_exit(char **cmd)
{
	if (cmd[1] && cmd[2])
	{
		printf("minishell: exit ;%s;: too many arguments\n", cmd[2]);
		return (g_spot.exit_status = 1, (void)0);
	}
	printf("exit\n");
	if (!cmd[1])
		free_exit(0);
	if (alpha_string(cmd[1]))
	{
		printf("bash: exit: %s: numeric argument required\n", cmd[1]);
		free_exit(2);
	}
	free_exit(exit_nbr(cmd[1]));
}

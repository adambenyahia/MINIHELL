/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:53 by beadam            #+#    #+#             */
/*   Updated: 2023/01/07 04:42:39 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int sig)
{
	if (g_spot.runing)
		return ;
	g_spot.exit_status = 128 + sig;
	printf("\n");
	rl_replace_line("",0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handler(void)
{
	signal(SIGINT, sig_int);
	// signal(SIGQUIT, SIG_IGN);

}
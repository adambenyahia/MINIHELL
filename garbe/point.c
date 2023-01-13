/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 07:50:48 by beadam            #+#    #+#             */
/*   Updated: 2023/01/13 00:10:58 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new(void *ptr)
{
	t_garb	*new;

	new = (t_garb *)malloc (sizeof(t_garb));
	if (!new)
	{
		perror("allocation exception :");
		free_exit(1);
	}
	new->ptr = ptr;
	new->next = NULL;
	if (!g_spot.g_garb)
		g_spot.g_garb = new;
	else
	{
		new->next = g_spot.g_garb;
		g_spot.g_garb = new;
	}
	return ;
}

void	*point(void *garb)
{
	if (!garb)
	{
		perror("allocation exception :");
		free_exit(1);
	}
	add_new(garb);
	return (garb);
}

void	free_exit(int exstatus)
{
	t_garb	*buff;

	while (g_spot.g_garb)
	{
		buff = g_spot.g_garb;
		g_spot.g_garb = g_spot.g_garb->next;
		free(buff->ptr);
		free(buff);
	}
	exit(exstatus);
}

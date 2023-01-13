/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 07:50:40 by beadam            #+#    #+#             */
/*   Updated: 2023/01/13 06:20:30 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARB_H
# define GARB_H

typedef struct s_garb
{
	void			*ptr;
	struct s_garb	*next;
}				t_garb;

void	add_new(void *ptr);
void	free_exit(int exstatus);
void	*point(void *garb);

#endif
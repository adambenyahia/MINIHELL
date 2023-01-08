/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:24:57 by beadam            #+#    #+#             */
/*   Updated: 2023/01/08 07:50:21 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// close(0); L1
void	pipe_helper(t_tree *cmd, t_env **env, int *fd, bool lr)
{
	if (lr)
		dup2(fd[1], 1);
	if (!lr)
		dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	exec(cmd, env);
}

void	piper(t_tree *cmd, t_env **env)
{
	int	leftpid;
	int	rightpid;
	int	fd[2];

	if (pipe(fd) == -1)
		return (printf("failed to pipe\n"), (void)0);
	leftpid = fork();
	if (leftpid == 0)
	{
		pipe_helper(cmd->left, env, fd, true);
		exit(0);
	}
	rightpid = fork();
	if (rightpid == 0)
	{
		pipe_helper(cmd->right, env, fd, false);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(leftpid, &g_spot.exit_status, 0);
	waitpid(rightpid, &g_spot.exit_status, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 04:05:20 by beadam            #+#    #+#             */
/*   Updated: 2023/01/11 11:16:16 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	exec_builtin(t_tree *cmd, t_env **env)
{
	if (!ft_strncmp(cmd->cmdlist->cmd, "echo", 5))
		return (ft_echo(cmdstring(cmd), cmd->file.out), true);
	else if (!ft_strncmp(cmd->cmdlist->cmd, "pwd", 4))
		return (pwd_cmd(cmdstring(cmd), cmd->file.out), true);
	else if (!ft_strncmp(cmd->cmdlist->cmd, "cd", 3))
		return (ft_cd(cmdstring(cmd), *env), true);
	else if (!ft_strncmp(cmd->cmdlist->cmd, "env", 4))
		return (ft_env(cmdstring(cmd), *env, cmd->file.out), true);
	else if (!ft_strncmp(cmd->cmdlist->cmd, "unset", 6))
		return (ft_unset(cmdstring(cmd), env), true);
	else if (!ft_strncmp(cmd->cmdlist->cmd, "export", 7))
		return (ft_export(cmdstring(cmd), env), true);
	return (false);
}

// char **etos(t_env *env)
// {
// 	char **array;
// 	int i;
// }

void	redirect(t_io_fd red)
{
	dup2(red.out, 1);
	if (red.out != 1)
		close(red.out);
	dup2(red.in, 0);
	if (red.in != 0)
		close(red.in);
}

void	waiter(int pid)
{
	int	ex;

	waitpid(pid, &ex, 0);
	if (!WIFEXITED(ex))
		return (g_spot.exit_status = 1, (void)0);
	g_spot.exit_status = WEXITSTATUS(ex);
}

void	exec_cmd(t_tree *cmd, t_env **env)
{
	int		pid;
	char	**cmdstr;
	char	*ptr;

	if (!cmd->cmdlist)
		return ;
	cmdstr = cmdstring(cmd);
	if (exec_builtin(cmd, env))
		return ;
	ptr = cmd_path(cmdstr[0], *env);
	pid = fork();
	if (pid == -1)
		return (perror("failed to create child process"));
	if (pid == 0)
	{
		redirect(cmd->file);
		execve(ptr, cmdstr, (*env)->tab);
		printf("minishell: %s: command not found\n", cmdstr[0]);
		g_spot.exit_status = 127;
		exit(127);
	}
	waiter(pid);
}

void	exec(t_tree *cmd, t_env **env)
{
	if (!cmd)
		return ;
	if (cmd->err < 0)
		return ;
	if (cmd->err > 0)
	{
		printf("minishell: %s\n", strerror(cmd->err));
		g_spot.exit_status = 1;
		return ;
	}
	g_spot.runing = 1;
	if (cmd->type == CMD)
		exec_cmd(cmd, env);
	if (cmd->type == PIPE)
		piper(cmd, env);
	g_spot.runing = 0;
}

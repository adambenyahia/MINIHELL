#include "minishell.h"

char **cmdstring(t_tree *node)
{
	t_cmdlist *cmdlist;
	int i;
	char **cmdstring;

	cmdstring = malloc(sizeof(char *) * (node->cmdlen + 1));
	if (!cmdstring)
		return (NULL);
	cmdlist = node->cmdlist;
	i = 0;
	while (cmdlist)
	{
		cmdstring[i] = cmdlist->cmd;
		cmdlist = cmdlist->next;
		i++;
	}
	cmdstring[i] = NULL;
	return (cmdstring);
}

static bool exec_builtin(t_tree *cmd, t_env **env)
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
	// else if (!ft_strncmp(cmd->cmdlist->cmd, "export", 7))
	// 	return (ft_export(cmdstring(cmd), env), true);
	return (false);
}

char *append_slash(char *str)
{
	if (!str)
		return (ft_strdup("/"));
	return (ft_strjoin(str, "/"));
}

char *cmd_path(char *cmd, t_env *env)
{
	char **path;
	char *var;
	int i;

	if (!cmd || !*cmd || !env)
		return (NULL);
	if (!access(cmd, X_OK | F_OK))
		return (cmd);
	i = 0;
	var = find_env("PATH", env);
	path = ft_split(var, ':');
	while (path[i])
	{
		path[i] = append_slash(path[i]);
		path[i] = ft_strjoin(path[i], cmd);
		if (!access(path[i], X_OK))
			return (path[i]);
		i++;
	}
	return (NULL);
}

// char **etos(t_env *env)
// {
// 	char **array;
// 	int i;
// }

void redirect(io_fd red)
{

	dup2(red.out, 1);
	if (red.out != 1)
		close(red.out);
	dup2(red.in, 0);
	if (red.in != 0)
		close(red.in);
}

void exec_cmd(t_tree *cmd, t_env **env)
{
	int pid;
	int ex;
	char **cmdstr;
	char *ptr;

	if (!cmd->cmdlist)
		return;
	ex = 0;
	cmdstr = cmdstring(cmd);
	if (exec_builtin(cmd, env))
		return;
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
	waitpid(pid, &ex, 0);
}

void exec(t_tree *cmd, t_env **env)
{
	if (!cmd)
		return;
	if (cmd->errorflag > 0)
	{
		printf("minishell: %s\n", strerror(cmd->errorflag));
		g_spot.exit_status = 1;
		return;
	}
	g_spot.runing = 1;
	if (cmd->type == CMD)
		exec_cmd(cmd, env);
	if (cmd->type == PIPE)
		piper(cmd, env);
	g_spot.runing = 0;
}
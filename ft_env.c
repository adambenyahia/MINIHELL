#include "minishell.h"

void	ft_env(char **cmd, t_env *env, int fd)
{
	t_key_value *tmp;
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
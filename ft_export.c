/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:25:12 by beadam            #+#    #+#             */
/*   Updated: 2023/01/13 07:12:47 by beadam           ###   ########.fr       */
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

t_key_value	*find_env2(char *key, t_env *env)
{
	t_key_value	*tmp;
	size_t		keylen;
	size_t		envlen;

	tmp = env->head;
	while (tmp)
	{
		keylen = ft_strlen(key);
		envlen = ft_strlen(tmp->key);
		if (keylen > envlen)
			envlen = keylen;
		if (!ft_strncmp(tmp->key, key, envlen))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_add_var(char **args, t_env **env)
{
	t_key_value	*node;

	if ((*env)->size == 0)
	{
		node = ft_create_node(args);
		(*env)->head = node;
		(*env)->tail = node;
		(*env)->size++;
		return ;
	}
	node = find_env2(args[0], *env);
	if (!node)
	{
		node = ft_create_node(args);
		(*env)->tail->next = node;
		(*env)->tail = node;
		(*env)->size++;
	}
	else
		node->value = args[1];
}

void	ft_export_var(char **cmd, int i, int j, t_env **env)
{
	char	**args;

	while (cmd[i][++j])
	{
		if (cmd[i][j] == '=')
		{
			args = ft_split_export(cmd[i], j, 1);
			ft_add_var(args, env);
			break ;
		}
		else if (cmd[i][j] == '+' && cmd[i][j + 1] == '=')
		{
			args = ft_split_export(cmd[i], j, 2);
			ft_append_var(args, env);
			break ;
		}
		else if (cmd[i][j] == '+' && cmd[i][j + 1] != '=')
		{
			g_spot.exit_status = 1;
			printf("minishell: export: `%s': not a valid identifier\n", \
				cmd[i]);
		}
	}
	if (j == (int)ft_strlen(cmd[i]))
		ft_add_var(ft_split_export(cmd[i], j, 0), env);
}

void	ft_export(char **cmd, t_env **env)
{
	int	i;
	int	j;

	i = 0;
	if (!cmd[1])
		return (display_env(*env));
	while (cmd[++i])
	{
		if (ft_isalpha(cmd[i][0]) || cmd[i][0] == '_')
		{
			j = -1;
			ft_export_var(cmd, i, j, env);
		}
		else
		{
			g_spot.exit_status = 1;
			printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
		}
	}
}

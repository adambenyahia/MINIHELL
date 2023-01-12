/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beadam <beadam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 03:57:23 by beadam            #+#    #+#             */
/*   Updated: 2023/01/11 14:01:18 by beadam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(char *key, t_env *env)
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
			return (tmp->value);
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

void	combine_words(t_tokens **head)
{
	t_tokens	*tokens;

	tokens = *head;
	while (tokens && tokens->next)
	{
		if (tokens->flag == WORD && tokens->next->flag == WORD)
		{
			tokens->token = ft_strjoin(tokens->token, tokens->next->token);
			node_del_dll(head, tokens->next);
			tokens = *head;
			continue ;
		}
		tokens = tokens->next;
	}
	tokens = *head;
	while (tokens)
	{
		if (tokens->flag == SP)
			node_del_dll(head, tokens);
		tokens = tokens->next;
	}
}

void	expand(t_env *env, t_tokens **head)
{
	t_tokens	*token;

	token = *head;
	while (token)
	{
		if (token->flag == VAR)
		{
			if (!ft_strncmp(token->token + 1, "?", 1))
				token->token = ft_itoa(g_spot.exit_status);
			else if (!ft_strncmp(token->token + 1, "0", 1))
				token->token = ft_strdup("minishell");
			else if (!ft_strncmp(token->token + 1, "$", 1))
				token->token = ft_itoa(getpid());
			else
				token->token = find_env(token->token + 1, env);
			token->flag = WORD;
		}
		token = token->next;
	}
	combine_words(head);
}

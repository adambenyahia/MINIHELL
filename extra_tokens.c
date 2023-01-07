#include "minishell.h"

void	remove_quotes(t_tokens **tokens)
{
	t_tokens	*node;

	node = *tokens;
	while (node)
	{
		if (node->flag == SQ || node->flag == DQ)
		{
			if (!node->next || node->next->flag != node->flag)
			{
				node_del_dll(tokens, node);
				node = *tokens;
				continue ;
			}
			else
			{
				node->flag = WORD;
				node->token = ft_strdup("");
				continue ;
			}
		}
		node = node->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 18:29:01 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/30 19:08:59 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_args(char **args, t_token **token_list)
{
	while (token_list && (*token_list)->type == T_IDENTIFIER)
	{
		
	}
}


t_node	*get_simple_cmd(t_token *token_list)
{
	t_node	*node;

	node = new_node(N_CMD);
	if (!node)
		return (error_msg("Memory allocation failed"), NULL);
	while (token_list && (token_list->type == T_IDENTIFIER)
		|| is_redirection(token_list->type))
	{
		if (token_list->type == T_IDENTIFIER)
		{
			join_args(&(node->args), &token_list);
		}
		else if (is_redirection(token_list->type))
		{
			//make io list
		}
	}
	return (node);
}
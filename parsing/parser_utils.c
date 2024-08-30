/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 16:29:35 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/30 18:40:23 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	curr_token_is_binop(t_token *token_list)
{
	if (!token_list)
		return (false);
	if (token_list->type == T_PIPE || token_list->type == T_AND
		|| token_list->type == T_OR)
		return (true);
	return (false);
}

void	get_next_token(t_token **token_list)
{
	*token_list = (*token_list)->next;
}

t_node	*new_node(t_node_type type)
{
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

bool	is_redirection(t_token_type type)
{
	if (type == T_DGREAT || type == T_DLESS
		|| type == T_LESS || type == T_GREAT)
		return (true);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 11:53:09 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/29 15:12:05 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token_list(t_token **token_list)
{
	t_token	*curr_node;
	t_token	*next;

	curr_node = *token_list;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		free(curr_node->value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*token_list = NULL;
}

t_token	*new_token_node(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	return (new_token);
}

void	token_lst_add_back(t_token **token_list, t_token *new_token)
{
	t_token	*curr_node;

	if (!*token_list)
	{
		*token_list = new_token;
		return ;
	}
	curr_node = *token_list;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new_token;
	new_token->prev = curr_node;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 18:29:01 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/29 16:09:27 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	join_args(char **args, t_token **token_list, t_data **data)
{
	char	*to_free;

	if ((*data)->parse_error == true)
		return (NULL);
	if (!*args)
		*args = ft_strdup("");
	if (!*args)
		return (false);
	while (token_list && *token_list && (*token_list)->type == T_IDENTIFIER)
	{
		to_free = *args;
		*args = ft_strjoin_with(*args, (*token_list)->value, ' ');
		if (!*args)
			return (free(to_free), false);
		free(to_free);
		get_next_token(token_list);
	}
	return (true);
}

bool	get_io_list(t_io_node **io_list, t_token **token_list, t_data **data)
{
	t_io_node		*temp_io_node;
	t_token_type	redir_type;

	if ((*data)->parse_error == true)
		return (NULL);
	while (token_list && *token_list
		&& is_redirection((*token_list)->type) == true)
	{
		redir_type = (*token_list)->type;
		get_next_token(token_list);
		if (!token_list || !*token_list)
			return ((*data)->parse_error = true,
				error_msg("Syntax error: redirection"), false);
		if ((*token_list)->type != T_IDENTIFIER)
			return ((*data)->parse_error = true,
				error_msg("Syntax error: redirection"), false);
		temp_io_node = new_io_node(redir_type, (*token_list)->value);
		if (!temp_io_node)
			return ((*data)->parse_error = true,
				error_msg("Memory allocation fail"), false);
		append_io_node(io_list, temp_io_node);
		get_next_token(token_list);
	}
	return (true);
}

t_node	*get_simple_cmd(t_token *token_list, t_data **data)
{
	t_node	*node;

	if ((*data)->parse_error == true)
		return (NULL);
	node = new_parse_node(N_CMD);
	if (!node)
		return ((*data)->parse_error = true,
			error_msg("Memory allocation failed"), NULL);
	while (token_list && (token_list->type == T_IDENTIFIER
			|| is_redirection(token_list->type) == true))
	{
		if (token_list->type == T_IDENTIFIER)
		{
			if (join_args(&(node->args), &token_list, data) == false)
				return (clear_cmd_node(node), (*data)->parse_error = true,
					error_msg("Memory allocation failed"), NULL);
		}
		else if (is_redirection(token_list->type) == true)
		{
			if (get_io_list(&(node->io_list), &token_list, data) == false)
				return (free(node->args), free(node), NULL);
		}
	}
	return (node);
}

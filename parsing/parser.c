/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 14:46:05 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/22 16:46:28 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*combine(t_node *left, t_node *right)
{
	t_node	*node;

	node = new_parse_node(N_PIPE);
	if (!node)
		return (error_msg("Memory allocation error"), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*term(t_token *token_list)
{
	if (token_list->type == T_PIPE)
		return (error_msg("Syntax error: operator before command"), NULL);
	else
		return (get_simple_cmd(token_list));
}

t_node	*handle_term_and_token(t_token **token_list)
{
	t_node	*left;

	if (!token_list)
		return (NULL);
	left = term(*token_list);
	if (!left)
		return (NULL);
	get_next_token(token_list);
	while (*token_list && (*token_list)->type == T_IDENTIFIER)
		get_next_token(token_list);
	return (left);
}

t_node	*expression(int min_prec, t_token **token_list)
{
	t_node			*left;
	t_node			*right;
	int				next_prec;

	left = handle_term_and_token(token_list);
	if (!left)
		return (NULL);
	while (*token_list && (*token_list)->type == T_PIPE && 0 >= min_prec)
	{
		get_next_token(token_list);
		if (!token_list || !*token_list)
			return (error_msg ("Syntax error: no command after '|'"),
				NULL);
		next_prec = 0 + 1;
		right = expression(next_prec, token_list);
		if (!right)
			return (left);
		left = combine(left, right);
		if (!left)
			return (clear_ast_nodes(&left, &right, *token_list), NULL);
	}
	return (left);
}

t_node	*parse(t_token *token_list)
{
	t_node	*ast;

	if (!token_list)
		return (NULL);
	ast = expression(0, &token_list);
	return (ast);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 14:46:05 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/17 18:41:05 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*combine(t_token_type op, t_node *left, t_node *right)
{
	t_node	*node;

	node = new_parse_node(get_node_type(op));
	if (!node)
		return (error_msg("Memory allocation error"), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*term(t_token *token_list)
{
	if (curr_token_is_binop(token_list))
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
	t_token_type	op;
	int				next_prec;

	left = handle_term_and_token(token_list);
	if (!left)
		return (NULL);
	while (curr_token_is_binop(*token_list)
		&& token_prec((*token_list)->type) >= min_prec)
	{
		op = (*token_list)->type;
		get_next_token(token_list);
		if (!token_list)
			return (error_msg ("Syntax error: no command after operator"),
				NULL);
		next_prec = token_prec(op) + 1;
		right = expression(next_prec, token_list);
		if (!right)
			return (left);
		left = combine(op, left, right);
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

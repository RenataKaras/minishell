/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 14:46:05 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/30 18:28:07 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*term(t_token *token_list)
{
	if (curr_token_is_binop(token_list) || token_list->type == T_C_PARENT)
		return (error_msg("Syntax error: operator before command"), NULL);
	else if (token_list->type == T_O_PARENT)
	{
		get_next_token(&token_list);
	}
	else
		return (get_simple_cmd(token_list));
}

t_node	*expression(int min_prec, t_token *token_list)
{
	t_node			*left;
	t_node			*right;
	t_token_type	op;
	int				next_prec;

	left = term(token_list);
}



void	parse(t_token *token_list)
{
	t_node	*ast;

	ast = expression(0, token_list);
}
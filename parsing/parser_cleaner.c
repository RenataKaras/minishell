/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_cleaner.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 15:06:49 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/06 16:12:01 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_char2(char **str)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	recursively_clear_ast(t_node *node)
{
	if (!node)
		return ;
	if (node->type == N_CMD)
		clear_cmd_node(node);
	else
	{
		if (node->left)
			recursively_clear_ast(node->left);
		if (node->right)
			recursively_clear_ast(node->right);
	}
	free(node);
}

void	clear_ast(t_node **ast, t_token *token_list)
{
	recursively_clear_ast(*ast);
	*ast = NULL;
	free_token_list(&token_list);
}

void	clear_io_list(t_io_node **lst)
{
	t_io_node	*current;
	t_io_node	*next;

	current = *lst;
	if (!current)
		return ;
	while (current)
	{
		free(current->value);
		free_char2(current->expanded_value);
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	clear_cmd_node(t_node *node)
{
	if (!node)
		return ;
	clear_io_list(&(node->io_list));
	free(node->args);
	free_char2(node->expanded_args);
}

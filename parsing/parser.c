/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 14:46:05 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/06 16:17:04 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_io_list(t_io_node *io_list, int depth)
{
	t_io_node	*curr_io = io_list;

	while (curr_io)
	{
		// Print indentation for tree structure visualization
		for (int i = 0; i < depth; i++)
			printf("  ");  // Two spaces for each level of depth

		// Print the type of IO redirection
		printf("IO Type: ");
		switch (curr_io->type)
		{
			case IO_IN:
				printf("Input Redirection (<)\n");
				break;
			case IO_OUT:
				printf("Output Redirection (>)\n");
				break;
			case IO_HEREDOC:
				printf("Heredoc (<<)\n");
				break;
			case IO_APPEND:
				printf("Append Output (>>)\n");
				break;
			default:
				printf("Unknown IO Type\n");
				break;
		}

		// Print the value (filename or heredoc delimiter)
		if (curr_io->value)
		{
			for (int i = 0; i < depth; i++)
				printf("  ");
			printf("IO Value: %s\n", curr_io->value);
		}

		// Print expanded_value if available
		if (curr_io->expanded_value)
		{
			for (int i = 0; curr_io->expanded_value[i]; i++)
			{
				for (int j = 0; j < depth; j++)
					printf("  ");
				printf("Expanded IO Value: %s\n", curr_io->expanded_value[i]);
			}
		}

		curr_io = curr_io->next;
	}
}

void	print_ast(t_node *node, int depth)
{
	if (!node)
		return;

	// Print indentation for tree structure visualization
	for (int i = 0; i < depth; i++)
		printf("  ");  // Two spaces for each level of depth

	// Print node type
	printf("Node Type: ");
	switch (node->type)
	{
		case N_PIPE:
			printf("PIPE\n");
			break;
		case N_AND:
			printf("AND\n");
			break;
		case N_OR:
			printf("OR\n");
			break;
		case N_CMD:
			printf("CMD\n");
			break;
		default:
			printf("Unknown\n");
			break;
	}

	// Print node's args
	if (node->args)
	{
		for (int i = 0; i < depth; i++)
			printf("  ");
		printf("Args: %s\n", node->args);
	}

	// Print expanded_args if present
	if (node->expanded_args)
	{
		for (int i = 0; node->expanded_args[i]; i++)
		{
			for (int j = 0; j < depth; j++)
				printf("  ");
			printf("Expanded Arg: %s\n", node->expanded_args[i]);
		}
	}

	// Print IO redirections if present
	if (node->io_list)
	{
		for (int i = 0; i < depth; i++)
			printf("  ");
		printf("IO Redirections:\n");
		print_io_list(node->io_list, depth + 1);
	}

	// Recursively print left and right children
	if (node->left)
	{
		for (int i = 0; i < depth; i++)
			printf("  ");
		printf("Left:\n");
		print_ast(node->left, depth + 1);
	}
	if (node->right)
	{
		for (int i = 0; i < depth; i++)
			printf("  ");
		printf("Right:\n");
		print_ast(node->right, depth + 1);
	}
}

t_node	*combine (t_token_type op, t_node *left, t_node *right)
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
	// printf("inside term\n");
	if (curr_token_is_binop(token_list) || token_list->type == T_C_PARENT)
		return (error_msg("Syntax error: operator before command"), NULL);
	// else if (token_list->type == T_O_PARENT)
	// {
	// 	get_next_token(&token_list);
	// }
	else
	{
		// printf("inside else\n");
		return (get_simple_cmd(token_list));
	}
}

t_node	*expression(int min_prec, t_token *token_list)
{
	t_node			*left;
	t_node			*right;
	t_token_type	op;
	int				next_prec;

	if (!token_list)
		return (NULL);
	left = term(token_list);
	if (!left)
		return (NULL);
	while (curr_token_is_binop(token_list)
		&& token_prec(token_list->type) >= min_prec)
	{
		op = token_list->type;
		get_next_token(&token_list);
		if (!token_list)
			return (error_msg ("Syntax error"), NULL);
		next_prec = token_prec(op) + 1;
		right = expression(next_prec, token_list);
		if (!right)
			return (left);
		left = combine(op, left, right);
		if (!left)
			return (clear_ast(&left, token_list),
				clear_ast(&right, token_list), NULL);
	}
	return (left);
}

void	parse(t_token *token_list)
{
	// printf("inside parse\n");	
	t_node	*ast;

	ast = expression(0, token_list);
	// print_ast(ast, 0);
}

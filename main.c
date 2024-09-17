/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/17 17:39:55 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env_list(t_token *head)
{
    t_token *current = head;

    while (current != NULL)
    {
        printf("Type: %u, Value: %s\n", current->type, current->value);
        current = current->next;
    }
}

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
				printf("Output Redirection (> or >>)\n");
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

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}

void	*maintain_prompt(t_data data)
{
	while (1)
	{
		data.cmd_line = readline("minishell> ");
		if (!data.cmd_line)
			return (error_msg("exit\n"), NULL);
		if (data.cmd_line[0])
			add_history(data.cmd_line);
		// input_checker(data.cmd_line);
		data.token_list = tokenize(data.cmd_line);
		if (!data.token_list)
			continue ;
		data.ast = parse(data.token_list);
		print_env_list (data.token_list);
		print_ast(data.ast, 0);
		//execution
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
		return (error_msg("Wrong number of arguments"), EXIT_FAILURE);
	data.envp = envp;
	data.env = copy_env(data.envp);
	if (!data.env)
		return (EXIT_FAILURE);
	// print_env_list(data.env);
	maintain_prompt(data);
	return (0);
}

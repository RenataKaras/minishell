/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/23 17:47:28 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_env_list(t_envls *list)
// {
//     while (list)
//     {
//         printf("Type: %u, Value: %s\n", current->type, current->value);
//         current = current->next;
//     }
//     printf("End of list.\n");
// }

// void	print_io_list(t_io_node *io_list, int depth)
// {
// 	t_io_node	*curr_io = io_list;

// 	while (curr_io)
// 	{
// 		// Print indentation for tree structure visualization
// 		for (int i = 0; i < depth; i++)
// 			printf("  ");  // Two spaces for each level of depth

// 		// Print the type of IO redirection
// 		printf("IO Type: ");
// 		switch (curr_io->type)
// 		{
// 			case IO_IN:
// 				printf("Input Redirection (<)\n");
// 				break;
// 			case IO_OUT:
// 				printf("Output Redirection (> or >>)\n");
// 				break;
// 			case IO_HEREDOC:
// 				printf("Heredoc (<<)\n");
// 				break;
// 			case IO_APPEND:
// 				printf("Append Output (>>)\n");
// 				break;
// 			default:
// 				printf("Unknown IO Type\n");
// 				break;
// 		}

// 		// Print the value (filename or heredoc delimiter)
// 		if (curr_io->value)
// 		{
// 			for (int i = 0; i < depth; i++)
// 				printf("  ");
// 			printf("IO Value: %s\n", curr_io->value);
// 		}

// 		// Print expanded_value if available
// 		if (curr_io->expanded_value)
// 		{
// 			for (int i = 0; curr_io->expanded_value[i]; i++)
// 			{
// 				for (int j = 0; j < depth; j++)
// 					printf("  ");
// 				printf("Expanded IO Value: %s\n", curr_io->expanded_value[i]);
// 			}
// 		}

// 		curr_io = curr_io->next;
// 	}
// }

// void	print_ast(t_node *node, int depth)
// {
// 	if (!node)
// 		return;

// 	// Print indentation for tree structure visualization
// 	for (int i = 0; i < depth; i++)
// 		printf("  ");  // Two spaces for each level of depth

// 	//Print node type
// 	printf("Node Type: ");
// 	switch (node->type)
// 	{
// 		case N_PIPE:
// 			printf("PIPE\n");
// 			break;
// 		case N_CMD:
// 			printf("CMD\n");
// 			break;
// 		default:
// 			printf("Unknown\n");
// 			break;
// 	}

// 	// Print node's args
// 	if (node->args)
// 	{
// 		for (int i = 0; i < depth; i++)
// 			printf("  ");
// 		printf("Args: %s\n", node->args);
// 	}

// 	// Print expanded_args if present
// 	if (node->expanded_args)
// 	{
// 		for (int i = 0; node->expanded_args[i]; i++)
// 		{
// 			for (int j = 0; j < depth; j++)
// 				printf("  ");
// 			printf("Expanded Arg: %s\n", node->expanded_args[i]);
// 		}
// 	}

// 	// Print IO redirections if present
// 	if (node->io_list)
// 	{
// 		for (int i = 0; i < depth; i++)
// 			printf("  ");
// 		printf("IO Redirections:\n");
// 		print_io_list(node->io_list, depth + 1);
// 	}

// 	// Recursively print left and right children
// 	if (node->left)
// 	{
// 		for (int i = 0; i < depth; i++)
// 			printf("  ");
// 		printf("Left:\n");
// 		print_ast(node->left, depth + 1);
// 	}
// 	if (node->right)
// 	{
// 		for (int i = 0; i < depth; i++)
// 			printf("  ");
// 		printf("Right:\n");
// 		print_ast(node->right, depth + 1);
// 	}
// }

//init_minishell
// Zero out the memory for the minishell structure.
// ft_memset sets all bytes of `data` to 0, effectively initializing it.
// Duplicate the fd for stdin (0) and store in `data.stdin`.
// it saves the current stdin so it can be restored later if needed.
// TCGETATTR: It retrieves the terminal settings using tcgetattr 
//and stores them in data->original_terminal.


//signal is a standard C function defined in <signal.h>
//Prototype: void (*signal(int sig, void (*handler)(int)))(int);
// when specified signal is received, like SIGINT (Ctrl+C) or SIGQUIT (Ctrl+\)
//signal reacts immediately and calls the corresponding handler function
//NO MATTER where in praogram you are in
//int sig: signal number, such as SIGQUIT, SIGINT
//void (*handler)(int): a pointer to a function
//prototype of handler: void handler(int signum)
//it only receives the signal number
//signal() is not a global variable but it sets up signal handling globally 

//why use the signal function instead of a if statement:
//Signals like SIGINT (Ctrl+C) or SIGQUIT (Ctrl+) can be sent to your program 
//by the OS at any time, even while the program is in the middle of executing 
//something else. It cannot be predicted exactly when they will arrive, so an 
//if statement won't catch them unless a constant check (which is impractical)
//signal function reacts immediately

//passing a pointer to struct in oppose to the whole struct
// to avoid copying the whole thing

//start_execution
//Set signal handler for SIGQUIT and Initialize the abstract syntax tree (AST)
//If heredoc initialization is signaled:Clear AST and token list
//Reset heredoc signal flag
//TCSANOW:terminal control set attributes NOW(without delay)reset terminal
//Execute the command node and store exit status
//Clear AST and token list after execution

//volatile sig_atomic_t g_signal_number;

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}

static void	init_minishell(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->envp = envp;
	make_env_list(data);
	data->stdin = dup(0);
	data->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &data->original_terminal);
}

static void	start_execution(t_data *data)
{
	signal(SIGQUIT, child_sigq_handler);
	set_exec_precedence(data->ast, data);
	if (data->heredoc_siginit)
		data->heredoc_siginit = false;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->original_terminal);
	data->exit_status = execute_node(data->ast, false, data);
	clear_ast(&data->ast, data->token_list);
}

void	*maintain_prompt(t_data *data)
{
	while (1)
	{
		handle_signals(PARENT);
		data->cmd_line = readline("minishell> ");
		if (!data->cmd_line)
			(ft_putstr_fd("exit\n", 1), exit(data->exit_status));
		if (data->cmd_line[0])
			add_history(data->cmd_line);
		data->token_list = tokenize(data->cmd_line);
		if (!data->token_list)
			continue ;
		data->ast = parse(data->token_list, data);
		if (data->parse_error == true)
		{
			handle_parse_error(data);
			continue ;
		}
		// print_env_list (token_list);
		// print_ast(data->ast, 0);
		start_execution(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;

	if (argc != 1 || argv[1])
		return (error_msg("Wrong number of arguments"), EXIT_FAILURE);
	init_minishell(&data, envp);
	maintain_prompt(&data);
	free_or_add_list(NULL, true);
	return (clean_minishell(&data), data.exit_status);
}

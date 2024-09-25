/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/25 18:28:41 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t signal_number = 0;

static void	init_minishell(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->envp = envp;
	make_env_list(data);
	data->stdin = dup(0);
	data->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &data->original_terminal);
}
// Zero out the memory for the minishell structure.
// ft_memset sets all bytes of `minishell` to 0, effectively initializing it.
// Duplicate the fd for stdin (0) and store in `minishell.stdin`.
// it saves the current stdin so it can be restored later if needed.
// TCGETATTR: Retrieve and save the current terminal attributes for stdin 
//to `minishell.original_terminal`.
// This allows restoring terminal settings later if they are modified.


// static void	start_execution(void)
// {
// }

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

// 	// Print node type
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

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}

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

//Explanation why use the signal function instead of a if statement:

//Signals like SIGINT (Ctrl+C) or SIGQUIT (Ctrl+) can be sent to your program 
//by the OS at any time, even while the program is in the middle of executing 
//something else. It cannot be predicted exactly when they will arrive, so an 
//if statement won't catch them unless a constant check (which is impractical)
//signal function reacts immediately



//passing a pointer to struct in oppose to the whole struct
// to avoid copying the whole thing


// static void	start_execution(t_data *data)
// {
// 	signal(SIGQUIT, sigquit_handler);
// 	init_tree(data);
// }
//***CHANGED DATA TO A PONTER BECAUSE START_EX NEEDS A POINTER TO IT**/
//otherwise start_executin gets a pointer to the copy rather tha
//and start_execution also needs to be called from inside the loop
//passing a pointer to struct in oppose to the whole struct
// to avoid copying the whole thing

void	*maintain_prompt(t_data *data)
{
	while (1)
	{
		init_signals(data);
		data->cmd_line = readline("minishell> ");
		if (!data->cmd_line)
			return (error_msg("exit\n"), NULL);
		if (data->cmd_line[0])
			add_history(data->cmd_line);
		// input_checker(data.cmd_line);
		data->token_list = tokenize(data->cmd_line);
		if (!data->token_list)
			continue ;
		data->ast = parse(data->token_list);
		// print_env_list (token_list);
		// print_ast(data.ast, 0);
		//start_execution(data);
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
	//data.envp = envp;
	//data.env = copy_env(data.envp);
	//if (!data.env)
		//return (EXIT_FAILURE);
	//ft_exec_builtin(argv + 1, &data);// it was temporaty, skip the program name and send commands
	// print_env_list(data.env);
	return (0);
}

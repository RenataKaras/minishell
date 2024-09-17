/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/17 19:00:58 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
//         printf("Key: %s, Value: %s\n", list->key, list->value);
//         list = list->next;
//     }
//     printf("End of list.\n");
// }

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}

//do we need the whole struct here or just a pointer to the struct???
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
		// print_env_list (token_list);
		// print_ast(data.ast, 0);
		//execution
	}
}
//The signal function is a standard C func, 
//It is defined in the header file <signal.h>
//Prototype: void (*signal(int sig, void (*handler)(int)))(int);
//int sig: signal number, such as SIGQUIT, SIGINT, or other predefined signal
//from signal.h.
//void (*handler)(int): a pointer to a function 
//that takes an integer (the signal number) as an argument and returns void.
//SIGQUIT is sent when the user presses Ctrl+\. 
//It causes the program to quit and may create a core dump (for debugging).
//passing a pointer to struct in oppose to the whole struct
// to avoid copying the whole thing

static void	start_execution(t_data *data)
{
	signal(SIGQUIT, sigquit_handler);
	
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;

	if (argc != 1 && argv[1])
		return (error_msg("Wrong number of arguments"), EXIT_FAILURE);
	// data.envp = envp;
	// data.env = copy_env(data.envp);
	// if (!data.env)
	// 	return (EXIT_FAILURE);
	init_minishell(&data, envp);
	maintain_prompt(data);
	start_execution(&data);
	//ft_exec_builtin(argv + 1, &data);// it was temporaty, skip the program name and send commands
	// print_env_list(data.env);
	
	return (0);
}

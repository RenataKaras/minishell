/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/16 15:12:00 by rshaheen      ########   odam.nl         */
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


// void print_env_list(t_envls *head)
// {
//     t_envls *current = head;

//     while (current != NULL)
//     {
//         printf("Keyword: %s, Info: %s\n", current->keyword, current->info);
//         current = current->next;
//     }
// }

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}

void	maintain_prompt(t_data data)
{
	while (1)
	{
		data.cmd_line = readline("minishell> ");
		add_history(data.cmd_line);
		input_checker(data.cmd_line);
		cmd_parser(&data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;

	if (argc != 1 && argv)
		return (error_msg("Wrong number of arguments"), EXIT_FAILURE);
	data.envp = envp;
	data.env = copy_env(data.envp);
	init_minishell(&data, envp);
	//start_execution();
	if (argc > 1)
		ft_exec_builtin(argv + 1, &data);//skip the program name and send commands
	// print_env_list(data.env);
	maintain_prompt(data);
	return (0);
}

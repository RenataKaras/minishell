/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/16 14:53:19 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_minishell(t_data *minishell, char **envp)
{
	ft_memset(minishell, 0, sizeof(t_data));
	minishell->envp = envp;
	make_env_list(minishell);
	minishell->stdin = dup(0);
	minishell->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &minishell->original_terminal);
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

int	main(int argc, char **argv, char **envp)
{
	t_data	minishell;
	((void)argc, (void)argv);

	init_minishell(&minishell, envp);
	//start_execution();
	if (argc > 1)
		ft_exec_builtin(argv + 1, &minishell);//skip the program name and send commands
	return (0);
}

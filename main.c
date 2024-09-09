/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/09 16:27:37 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

static void	init_minishell(char **envp)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.env = envp;
	make_env_list();
	g_minishell.stdin = dup(0);
	g_minishell.stdout = dup(1);
	tcgetattr(STDIN_FILENO, &g_minishell.original_term);
}
// Zero out the memory for the global `g_minishell` structure.
// ft_memset sets all bytes of `g_minishell` to 0, effectively initializing it.
// Duplicate the fd for stdin (0) and store in `g_minishell.stdin`.
// it saves the current stdin so it can be restored later if needed.
// TCGETATTR: Retrieve and save the current terminal attributes for stdin 
//to `g_minishell.original_term`.
// This allows restoring terminal settings later if they are modified.

static void	start_execution(void)
{
	
}

// void print_env_list(t_env *list)
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
	((void)argc, (void)argv);
	init_minishell(envp);
	start_execution();

	if (argc > 1)
		ft_exec_builtin(argv + 1);//skip the program name and send commands
	return (0);
}


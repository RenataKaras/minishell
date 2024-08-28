/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/28 18:08:33 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_minishell(char **envp)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.env = envp;
	copy_envp();
	g_minishell.stdin = dup(0);
	g_minishell.stdout = dup(1);
}
// Zero out the memory for the global `g_minishell` structure.
// ft_memset sets all bytes of `g_minishell` to 0, effectively initializing it.
// Duplicate the fd for stdin (0) and store in `g_minishell.stdin`.
// it saves the current stdin so it can be restored later if needed.
//same for stdout

int	main(int argc, char **argv, char **envp)
{
	((void)argc, (void)argv);
	ft_init_minishell(envp);

	// if (argc > 1)
	// 	ft_exec_builtin(argv + 1);//skip the program name and send commands
	return (0);
}


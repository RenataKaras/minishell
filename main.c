/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/27 18:07:06 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	ft_init_minishell(char **env)
{
	// Zero out the memory for the global `g_minishell` structure.
    // `ft_memset` is used to set all bytes of `g_minishell` to 0, effectively initializing it.
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	ft_init_envlst();
	g_minishell.env = env;
	// Duplicate the file descriptor for standard input (0) and store it in `g_minishell.stdin`.
	// This allows for saving the current standard input so it can be restored later if needed.
	g_minishell.stdin = dup(0);
	g_minishell.stdout = dup(1);//same for output
}
int	main(int argc, char **argv, char **env)
{
	((void)argc, (void)argv);
	ft_init_minishell(env);

	// if (argc > 1)
	// 	ft_exec_builtin(argv + 1);//skip the program name and send commands
	return (0);
}

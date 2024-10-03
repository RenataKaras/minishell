/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 18:37:27 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/03 11:51:04 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(char **command, t_data *minishell)
{
	puts("here");
	if (ft_strncmp(command[0], "pwd", 3) == 0)
		return (ft_pwd());
	if (ft_strncmp(command[0], "echo", 4) == 0)
		return (ft_echo(command));
	if (ft_strncmp(command[0], "envp", 3) == 0)
		return (ft_env(minishell));
	if (ft_strcmp(command[0], "unset") == 0)
		return (ft_unset(command, minishell));
	if (ft_strcmp(command[0], "cd") == 0)
		return (ft_cd(command[1], minishell));
	if (ft_strcmp(command[0], "export") == 0)
		return (ft_export(command, minishell));
	return (ENO_GENERAL);
}


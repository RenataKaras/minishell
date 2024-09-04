/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 18:37:27 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/04 18:01:39 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(char **command)
{
	if (ft_strncmp(command[0], "pwd", 3) == 0)
		return (ft_pwd());
	if (ft_strncmp(command[0], "echo", 4) == 0)
		return (ft_echo(command));
	if (ft_strncmp(command[0], "env", 3) == 0)
		return (ft_env());
	if (ft_strcmp(command[0], "unset") == 0)
		return (ft_unset(command));
	if (ft_strcmp(command[0], "cd") == 0)
		return (ft_cd(command[1]));
	return (ENO_GENERAL);
}


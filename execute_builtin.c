/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 18:37:27 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/02 16:46:23 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(char **command)
{
	if (ft_strncmp(command[0], "pwd", 3) == 0)//we dont have strcmp
		return (ft_pwd());
	if (ft_strncmp(command[0], "echo", 4) == 0)
		return (ft_echo(command));
	if (ft_strncmp(command[0], "env", 3) == 0)
		return(ft_env());
	return (1);
}


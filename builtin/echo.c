/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 15:54:33 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/17 18:02:27 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//checks for -n flag
//returns 0 if -n is not found
//returns 1 ONLY if -n is found

static int	skip_newline(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (0);
	i++;
	if (s[1] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
//i = 1 cause begin at command #2 to check for flag and NULL
//enter in while loop in both -n and not -n cases
//check if there is more texts coming up
//print a space

int	ft_echo(char **command)
{
	int	i;
	int	skip_newline_flag;

	i = 1;
	skip_newline_flag = 0;
	while (command[i] != NULL && skip_newline(command[i]) == 1)
	{
		skip_newline_flag = 1;
		i++;
	}
	while (command[i])
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (skip_newline_flag == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}

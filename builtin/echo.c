/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 15:54:33 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/08/27 15:58:17 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//checks for -n flag
//returns 0 if -n is not found
//returns 1 if -n is found

static int	skip_newline(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (0);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **command)
{
	int	i;
	int	skip_newline_flag;

	i = 1;//begin at command #2 to check for flag and NULL
	skip_newline_flag = 0;
	while (command[i] != NULL && skip_newline(command[i]) == 1)
	{
		skip_newline_flag = 1;
		i++;
	}
	while (command[i])//enter here in both -n and not -n cases
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1])//check if there is more texts coming up
			ft_putstr_fd(" ", 1);//print a space
		i++;
	}
	if (skip_newline_flag == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
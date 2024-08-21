/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/19 18:37:20 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/08/21 17:18:22 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data, char **command, int fd)
{
	t_envls	*head;

	if (command[2] != NULL)
	{
		write(2, "env: ", 5);
		write(2, command[2], ft_strlen(command[2]));
		write(2, ": no such file or directory\n", 29);
		exit (127);
	}
	else
	{
		head = data->env;
		while (head != NULL)
		{
			ft_putstr_fd(head->keyword, fd);
			ft_putendl_fd(head->info, fd);
			head = head->next;
		}
	}
}

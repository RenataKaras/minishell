/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expander.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/03 13:39:03 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/07 16:49:51 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//skip the index of $ and store the start position of the string there
//if we got a ? after $, we will write the exit status
//go to the end of the name until it ends by
//NULL, or another '$' or space
//if end is bigger than start, we have a name of env variable
//add it to my static list. The static list (node_collection) is defined 
//within the free_or_add_list function. 
//It persists throughout the program's execution.
//It helps manage dynamically allocated memory for strings by keeping 
//track of them in a linked list,
//allowing for easy cleanup when necessary.
//get the value of the env variable 
//store it in tmp and write it

static int	write_env_value(char *name, size_t i, int write_fd, t_data *data)
{
	size_t	start;
	char	*tmp;

	start = ++i;
	if (name[i] == '?')
		return (ft_putnbr_fd(data->exit_status, write_fd), 2);
	while (name[i] && name[i] != '$' && name[i] != ' ')
		i++;
	if (i != start)
	{
		tmp = free_or_add_list(ft_substr(name, start, i), false);
		tmp = get_envlst_val(tmp, data->env);
		if (tmp)
			ft_putstr_fd(tmp, write_fd);
	}
	return (i);
}

void	heredoc_expander(char *str, int write_fd, t_data *data)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i += write_env_value(str, i, write_fd, data);
		else
			i += (ft_putchar_fd(str[i], write_fd), 1);
	}
	ft_putchar_fd('\n', write_fd);
}

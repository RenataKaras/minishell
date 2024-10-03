/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expander.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/03 13:39:03 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/03 13:48:08 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_heredoc_expand_writer(char *str, size_t i, int fd, t_data *data)
{
	size_t	start;
	char	*tmp;

	start = ++i;
	if (str[i] == '?')
		return (ft_putnbr_fd(data->exit_status, fd), 2);
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (i != start)
	{
		tmp = free_or_add_list(ft_substr(str, start, i), false);
		tmp = get_envlst_val(tmp, data->env);
		if (tmp)
			ft_putstr_fd(tmp, fd);
	}
	return (i);
}

void	heredoc_expander(char *str, int fd, t_data *data)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i += ft_heredoc_expand_writer(str, i, fd, data);
		else
			i += (ft_putchar_fd(str[i], fd), 1);
	}
	ft_putchar_fd('\n', fd);
}

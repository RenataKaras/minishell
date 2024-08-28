/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 17:18:36 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/26 18:28:45 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_separator(char **line_ptr, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
		append_separator(T_DLESS, line_ptr, token_list);
		
}


t_token	*tokenization(char *cmd_line)
{
	t_token	*token_list;

	token_list = NULL;
	while (*cmd_line)
	{
		if (is_space(*cmd_line))
			skip_spaces(&cmd_line);
		if (!ft_strncmp(cmd_line, "<", 1) || !ft_strncmp(cmd_line, ">", 1)
			|| !ft_strncmp(cmd_line, "|", 1) || !ft_strncmp(cmd_line, "&&", 2)
			|| !ft_strncmp(cmd_line, "(", 1) || !ft_strncmp(cmd_line, ")", 1))
			handle_separator(&cmd_line, &token_list);
	}
	return (token_list);
}

void	tokenize(char *cmd_line)
{
	t_token	*token_list;

	token_list = tokenization(cmd_line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 17:18:36 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/24 16:03:54 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_separator(char **line_ptr, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
		return (add_separator(T_DLESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		return (add_separator(T_DGREAT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "<", 1))
		return (add_separator(T_LESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">", 1))
		return (add_separator(T_GREAT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "&&", 2))
		return (error_msg("Syntax error: use of &&"), 0);
	else if (!ft_strncmp(*line_ptr, "(", 1) || !ft_strncmp(*line_ptr, ")", 1))
		return (error_msg("Syntax error: use of parenthesis"), 0);
	else if (!ft_strncmp(*line_ptr, "\\", 1) || !ft_strncmp(*line_ptr, ";", 1))
		return (error_msg("Syntax error: use of \\ or ;"), 0);
	else
		return (add_separator(T_PIPE, line_ptr, token_list) && 1);
}

//do we need && here?
t_token	*tokenization(char *cmd_line)
{
	t_token	*token_list;
	int		error_flag;

	token_list = NULL;
	error_flag = 0;
	while (*cmd_line)
	{
		if (error_flag == 1)
			return (free_token_list(&token_list), NULL);
		if (is_space(*cmd_line))
			skip_spaces(&cmd_line);
		else if (!ft_strncmp(cmd_line, "<", 1) || !ft_strncmp(cmd_line, ">", 1)
			|| !ft_strncmp(cmd_line, "|", 1) || !ft_strncmp(cmd_line, "&&", 2)
			|| !ft_strncmp(cmd_line, "(", 1) || !ft_strncmp(cmd_line, ")", 1)
			|| !ft_strncmp(cmd_line, "\\", 1) || !ft_strncmp(cmd_line, ";", 1))
			error_flag = (!handle_separator(&cmd_line, &token_list) && 1);
		else
			error_flag = (!add_identifier(&cmd_line, &token_list) && 1);
	}
	return (token_list);
}

t_token	*tokenize(char *cmd_line)
{
	t_token	*token_list;

	token_list = tokenization(cmd_line);
	return (token_list);
}

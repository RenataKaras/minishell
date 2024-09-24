/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_adder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 15:28:21 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/24 15:47:22 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_identifier(char **line_ptr, t_token **token_list)
{
	char	*temp_line;
	char	*value;
	t_token	*token;
	int		i;

	temp_line = *line_ptr;
	i = 0;
	while (temp_line[i] && is_separator(&temp_line[i]) == false)
	{
		if (is_quote(temp_line[i]) == true)
		{
			if (skip_quotes(temp_line, &i) == false)
				return (error_msg("Syntax error: unclosed quotes"), 0);
		}
		else
			i++;
	}
	value = ft_substr(temp_line, 0, i);
	if (!value)
		return (free(value), 0);
	token = new_token_node(value, T_IDENTIFIER);
	if (!token)
		return (free(value), 0);
	*line_ptr = *line_ptr + i;
	return (token_lst_add_back(token_list, token), 1);
}

int	add_separator(t_token_type type, char **line_ptr,
	t_token **token_list)
{
	t_token	*token;

	token = new_token_node(NULL, type);
	if (!token)
		return (0);
	token_lst_add_back(token_list, token);
	(*line_ptr)++;
	if (type == T_DLESS || type == T_DGREAT)
		(*line_ptr)++;
	return (1);
}

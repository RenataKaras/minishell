/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizing_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 17:39:08 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/12 13:07:58 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	skip_quotes(char *line, int *i)
{
	char	quote;

	quote = line[*i];
	if (ft_strchr(&line[*i + 1], quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

bool	is_separator(char *s)
{
	if (!ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t'
		|| *s == '<' || *s == '>' || *s == '|')
		return (true);
	return (false);
}

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	else
		return (false);
}

void	skip_spaces(char **line)
{
	while (**line && is_space(**line) == true)
		(*line)++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 17:55:17 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/08 17:06:10 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_normal_str(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

bool	is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

char	*handle_squotes(char *str, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dquote_str(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dquotes(t_data *data, int *i, char *str)
{
	char	*result;

	result = ft_strdup("\"");
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			result = strjoin_free(result, handle_dollar(data, i, str));
		else
			result = strjoin_free(result, handle_dquote_str(str, i));
	}
	(*i)++;
	return (strjoin_free(result, ft_strdup("\"")));
}

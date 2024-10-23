/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strip_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 17:36:14 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/23 16:49:18 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	unquoted_strlen(char *str)
{
	int		i;
	int		len;
	char	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!quotes)
				quotes = str[i++]; //stores the quote position and THEN increments the i
			else if (str[i] == quotes)
				quotes = ((i++) && 0); //this is the same as quotes = 0, i++
			else
				// len++;
				len = len + (i++ || 1); //this is the same as len++, i++
		}
		else
			// len++;
			len = len + (i++ || 1);
		// i++;
	}
	if (quotes)
		len++;
	return (len);
}

static void	unquote(char *str, int *i, char *result, int *j)
{
	char	quotes;

	quotes = str[(*i)];
	(*i)++;
	while (str[*i] && str[*i] != quotes)
	{
		result[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
	if (str[*i] == quotes)
		(*i)++;
	else
	{
		result[*j] = quotes;
		(*j)++;
	}
}

char	*strip_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = ft_calloc(1 + unquoted_strlen(str), sizeof(char));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			unquote(str, &i, result, &j);
		else
		{
			result[j] = str[i];
			j++;
			i++;
		}
	}
	free(str);
	return (result);
}

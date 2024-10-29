/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_split.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:37:13 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/29 17:20:09 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_word(char *str, int *i)
{
	char	quotes;

	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] != '\'' && str[*i] != '"')
			(*i)++;
		else
		{
			quotes = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != quotes)
				(*i)++;
			if (str[*i] == quotes)
				(*i)++;
		}
	}
}

static char	**allocator(char *str, char **strs)
{
	int	start;
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			start = i;
			skip_word(str, &i);
			size = i - start + 1;
			if (size > 0)
				strs[j] = ft_calloc(size, sizeof(char));
			if (!strs[j])
				return (NULL);
			j++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (strs);
}

static void	words_filler(char *str, char **strs, int *i, int j)
{
	char	quotes;
	int		k;

	k = 0;
	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] != '\'' && str[*i] != '"')
			strs[j][k++] = str[(*i)++];
		else
		{
			quotes = str[(*i)++];
			strs[j][k++] = quotes;
			while (str[*i] && str[*i] != quotes)
				strs[j][k++] = str[(*i)++];
			if (str[*i] == quotes)
				strs[j][k++] = str[(*i)++];
		}
	}
}

static char	**filler(char *str, char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && strs[j])
	{
		if (str[i] != ' ')
		{
			words_filler(str, strs, &i, j);
			j++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (strs);
}

char	**expander_split(char *str)
{
	int		count;
	char	**strs;
	char	**tofree;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			count++;
			skip_word(str, &i);
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	strs = ft_calloc(count + 1, sizeof(char *));
	tofree = strs;
	strs = allocator(str, strs);
	if (!strs || !count)
		return (free_char2(tofree), NULL);
	return (filler(str, strs));
}

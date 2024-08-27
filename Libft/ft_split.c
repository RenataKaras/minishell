/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 15:30:39 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/26 14:42:23 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **array)
{
	size_t	aindex;

	aindex = 0;
	while (array[aindex])
	{
		free(array[aindex]);
		aindex++;
	}
	free (array);
	return (NULL);
}

static size_t	ft_wrdcount(const char *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			in_word = 0;
			i++;
		}
		else
		{
			if (in_word == 0)
			{
				in_word = 1;
				count++;
			}
			i++;
		}
	}
	return (count);
}

static char	**ft_crearray(char **array, const char *s, char c)
{
	size_t	i;
	size_t	aindex;
	size_t	start;

	i = 0;
	aindex = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			start = i;
			while (s[i] != '\0' && s[i] != c)
				i++;
			array[aindex] = ft_substr (s, start, i - start);
			if (array[aindex] == NULL)
				return (ft_free(array));
			aindex++;
		}
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;

	if (!s || *s == '\0')
	{
		array = (char **)malloc(sizeof(char *));
		if (!array)
			return (NULL);
		array[0] = NULL;
		return (array);
	}
	words = ft_wrdcount(s, c) + 1;
	array = (char **) malloc(words * sizeof(char *));
	if (!array)
		return (NULL);
	array = ft_crearray(array, s, c);
	if (!array)
		return (NULL);
	array[words - 1] = NULL;
	return (array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 14:25:18 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/01 15:21:20 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strjoin_free(char *s1, char *s2)
{
	size_t	totals;
	char	*newstring;

	totals = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstring = (char *) malloc (totals * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	ft_strlcpy(newstring, (char *) s1, ft_strlen(s1) + 1);
	ft_strlcat(newstring, s2, totals);
	return (free(s1), free(s2), newstring);
}

char	*clean_empty_strs(char *str)
{
	int		i;
	int		j;
	char	*temp;
	char	*result;
	int		destsize;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2])
		|| (str[0] == '"' && str[1] == '"' && !str[2]))
		return (str);
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '"' && str[i + 1] == '"'))
			i = i + 2;
		else
			temp[j++] = str[i++];
	}
	free(str);
	destsize = ft_strlen(temp) + 1;
	result = ft_calloc(destsize, sizeof(char));
	return (ft_strlcpy(result, temp, destsize), free(temp), result);
}

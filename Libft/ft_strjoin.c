/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 14:00:22 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 11:43:21 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	totals;
	char	*newstring;

	totals = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstring = (char *) malloc (totals * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	ft_strlcpy(newstring, (char *) s1, ft_strlen(s1) + 1);
	ft_strlcat(newstring, s2, totals);
	return (newstring);
}

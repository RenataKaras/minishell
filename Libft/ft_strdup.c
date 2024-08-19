/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 14:35:03 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 17:46:28 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	n;
	char	*s1;

	n = ft_strlen(s) + 1;
	s1 = (char *) malloc(n * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	ft_strlcpy(s1, s, n);
	return (s1);
}

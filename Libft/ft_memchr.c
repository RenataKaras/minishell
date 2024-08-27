/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 15:08:18 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 14:16:50 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str1;
	char		ch;
	size_t		i;

	str1 = s;
	ch = (char) c;
	i = 0;
	while (i < n)
	{
		if (str1[i] == ch)
			return ((void *)&str1[i]);
		i++;
	}
	return (NULL);
}

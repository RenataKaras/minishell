/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 16:03:25 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 14:04:28 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*char1;
	const unsigned char	*char2;
	size_t				i;

	char1 = s1;
	char2 = s2;
	i = 0;
	while (i < n)
	{
		if (char1[i] != char2[i])
			return (char1[i] - char2[i]);
		i++;
	}
	return (0);
}

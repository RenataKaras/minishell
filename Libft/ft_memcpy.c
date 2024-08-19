/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 13:09:22 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 13:53:27 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest1;
	const char	*src1;
	size_t		i;

	dest1 = dest;
	src1 = src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}

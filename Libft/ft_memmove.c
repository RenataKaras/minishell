/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 16:07:43 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 13:53:19 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest1;
	const char	*src1;

	dest1 = dest;
	src1 = src;
	if (!dest1 && !src1)
		return (NULL);
	if (dest1 == src1)
		return ((void *)src1);
	if (dest < src)
		ft_memcpy(dest1, src1, n);
	else
	{
		while (n > 0)
		{
			dest1[n - 1] = src1[n - 1];
			n--;
		}
	}
	return (dest1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 16:43:46 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 11:41:48 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*chars;
	size_t	i;

	chars = s;
	i = 0;
	while (i < n)
	{
		chars[i] = c;
		i++;
	}
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 12:49:04 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 11:40:22 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*chars;
	size_t	i;

	chars = s;
	i = 0;
	while (i < n)
	{
		chars[i] = '\0';
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 16:15:29 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 17:58:38 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	n = 0;
	if (little[n] == '\0')
		return ((char *) big);
	while ((big[n] != '\0') && n < len)
	{
		i = 0;
		while (big[n + i] == little[i] && i + n < len)
		{
			i++;
			if (little[i] == '\0')
				return ((char *)&big[n]);
		}
		n++;
	}
	return (0);
}

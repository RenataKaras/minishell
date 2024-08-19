/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 17:04:41 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/31 12:02:44 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	leng;

	leng = 0;
	while (s[leng] != '\0')
		leng++;
	while (leng >= 0)
	{
		if (s[leng] == (char)c)
			return ((char *)&s[leng]);
		leng--;
	}
	return (NULL);
}

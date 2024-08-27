/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 11:49:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/04/11 15:53:59 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	cleanup_buffer(char *dst, char *src)
{
	size_t	i;

	i = 0;
	if (!src)
		return ;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*find_newline(char *buffer)
{
	size_t	i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (&buffer[i + 1]);
		i++;
	}
	return (NULL);
}

void	ft_strlcpy1(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		if (src[i] == '\n')
			return ;
		i++;
	}
}

size_t	ft_strlen1(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}

void	*ft_calloc1(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

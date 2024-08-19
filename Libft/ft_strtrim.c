/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 10:36:31 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 16:04:35 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1copy;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) && s1[start] != '\0')
		start++;
	while (ft_strrchr(set, s1[end - 1]) && end > start)
		end--;
	s1copy = (char *) malloc((end - start + 1) * sizeof(char));
	if (s1copy == NULL)
		return (NULL);
	ft_strlcpy(s1copy, &s1[start], end - start + 1);
	return (s1copy);
}

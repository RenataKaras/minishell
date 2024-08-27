/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 11:49:53 by rkaras        #+#    #+#                 */
/*   Updated: 2024/04/11 15:55:22 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin1(char *line, char *buffer)
{
	size_t	totals;
	char	*newstring;

	totals = ft_strlen1(line) + ft_strlen1(buffer);
	newstring = ft_calloc1 (totals + 1, sizeof(char));
	if (!newstring)
	{
		free(line);
		return (NULL);
	}
	ft_strlcpy1(newstring, line);
	ft_strlcpy1(&newstring[ft_strlen1(line)], buffer);
	free(line);
	return (newstring);
}

char	*read_and_join(int fd, char *line, char *buffer)
{
	int	bytes_read;

	bytes_read = 1;
	if (buffer[0] != '\0')
	{
		line = ft_strjoin1(line, buffer);
		if (!line)
			return (NULL);
	}
	while (bytes_read != 0 && !find_newline(buffer))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			buffer[0] = '\0';
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		line = ft_strjoin1(line, buffer);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_calloc1(1, sizeof(char));
	if (!line)
		return (NULL);
	line = read_and_join(fd, line, buffer);
	if (!line)
		return (NULL);
	if (buffer[0] != '\0')
		cleanup_buffer(buffer, find_newline(buffer));
	if (ft_strlen1(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i = 1;
// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	while(line)
// 	{
// 		printf("Line[%d]|%s|", i, line);
// 		printf("\n");
// 		i++;
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	close(fd);
// }

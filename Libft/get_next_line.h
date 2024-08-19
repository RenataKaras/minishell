/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 11:49:58 by rkaras        #+#    #+#                 */
/*   Updated: 2024/04/11 15:54:16 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
void	*ft_calloc1(size_t nmemb, size_t size);
char	*read_and_join(int fd, char *line, char *buffer);
void	ft_strlcpy1(char *dst, char *src);
size_t	ft_strlen1(const char *s);
char	*ft_strjoin1(char *line, char *buffer);
char	*find_newline(char *buffer);
void	cleanup_buffer(char *dst, char *src);

#endif
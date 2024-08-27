/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_printf.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 13:39:22 by rkaras        #+#    #+#                 */
/*   Updated: 2023/12/05 16:27:15 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_printf(char *s, int fd)
{
	if (!s)
		s = "(null)";
	ft_putstr_fd(s, fd);
	return ((int)ft_strlen(s));
}

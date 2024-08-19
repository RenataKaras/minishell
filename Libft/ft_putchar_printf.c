/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_printf.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 13:16:16 by rkaras        #+#    #+#                 */
/*   Updated: 2023/12/07 12:54:42 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_printf(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

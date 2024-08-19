/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_printf.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:06:32 by rkaras        #+#    #+#                 */
/*   Updated: 2023/12/05 15:21:36 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_printf(int n, int fd)
{
	char	*number;
	int		counter;

	number = ft_itoa(n);
	counter = ft_putstr_printf(number, fd);
	free(number);
	return (counter);
}

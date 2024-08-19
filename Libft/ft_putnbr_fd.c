/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 16:15:33 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 11:42:20 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digitno(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;
	int			digits;
	char		number[12];

	nb = n;
	digits = ft_digitno(nb);
	number[digits] = '\0';
	if (nb == 0)
		number[0] = '0';
	if (nb < 0)
	{
		number[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		digits--;
		number[digits] = (nb % 10) + '0';
		nb = nb / 10;
	}
	ft_putstr_fd(number, fd);
}

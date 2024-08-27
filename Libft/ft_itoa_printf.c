/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_printf.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:32:01 by rkaras        #+#    #+#                 */
/*   Updated: 2023/12/05 16:17:43 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_digitno(unsigned int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

int	ft_itoa_printf(unsigned int n)
{
	char	*number;
	int		digits;
	int		counter;

	digits = ft_digitno(n);
	number = (char *)malloc((digits + 1) * sizeof(char));
	if (!number)
		return (0);
	number[digits] = '\0';
	if (n == 0)
		number[0] = '0';
	while (n > 0)
	{
		digits--;
		number[digits] = (n % 10) + '0';
		n = n / 10;
	}
	counter = ft_putstr_printf(number, 1);
	free (number);
	return (counter);
}

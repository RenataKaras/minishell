/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pointhex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:09:15 by rkaras        #+#    #+#                 */
/*   Updated: 2023/12/05 15:30:31 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_digitno(unsigned long n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

int	ft_pointhex(unsigned long n, char *hex)
{
	unsigned long	digits;
	char			*hex_no;
	int				counter;

	if (n == 0)
		return (ft_putstr_printf("(nil)", 1));
	else
	{
		digits = ft_digitno(n) + 2;
		hex_no = (char *) malloc((digits + 1) * sizeof(char));
		if (!hex_no)
			return (0);
		hex_no[0] = '0';
		hex_no[1] = 'x';
		hex_no[digits] = '\0';
		while (n > 0)
		{
			digits--;
			hex_no[digits] = hex[n % 16];
			n = n / 16;
		}
		counter = ft_putstr_printf(hex_no, 1);
		free(hex_no);
	}
	return (counter);
}

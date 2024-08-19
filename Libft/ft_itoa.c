/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 13:57:46 by rkaras        #+#    #+#                 */
/*   Updated: 2023/10/25 11:41:40 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digitno(int n)
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

char	*ft_populatestr(char *number, long int nb, int digits)
{
	number[digits] = '\0';
	if (nb == 0)
	{
		number[0] = '0';
		return (number);
	}
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
	return (number);
}

char	*ft_itoa(int n)
{
	char		*number;
	long int	nb;
	int			digits;

	nb = n;
	digits = ft_digitno(nb);
	number = (char *) malloc((digits + 1) * sizeof(char));
	if (number == NULL)
		return (NULL);
	ft_populatestr(number, nb, digits);
	return (number);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 12:32:16 by rkaras        #+#    #+#                 */
/*   Updated: 2023/12/08 15:18:44 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_argtype_printf(va_list args, const char *arg_type, int i)
{
	int	counter;

	counter = 0;
	if (arg_type[i] == '%')
		counter += ft_putchar_printf('%', 1);
	else if (arg_type[i] == 'c')
		counter += ft_putchar_printf(va_arg(args, int), 1);
	else if (arg_type[i] == 's')
		counter += ft_putstr_printf(va_arg(args, char *), 1);
	else if (arg_type[i] == 'p')
		counter += ft_pointhex(va_arg(args, unsigned long), "0123456789abcdef");
	else if (arg_type[i] == 'd' || arg_type[i] == 'i')
		counter += ft_putnbr_printf(va_arg(args, int), 1);
	else if (arg_type[i] == 'u')
		counter += ft_itoa_printf(va_arg(args, unsigned int));
	else if (arg_type[i] == 'x')
		counter += ft_inthex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (arg_type[i] == 'X')
		counter += ft_inthex(va_arg(args, unsigned int), "0123456789ABCDEF");
	return (counter);
}

int	ft_printf(const char *arg_type, ...)
{
	int		counter;
	int		i;
	va_list	args;

	counter = 0;
	i = 0;
	if (!arg_type)
		return (0);
	va_start(args, arg_type);
	while (arg_type[i] != '\0')
	{
		if (arg_type[i] == '%')
		{
			i++;
			if (arg_type[i] == '\0')
				return (-1);
			counter += ft_argtype_printf(args, arg_type, i);
		}
		else
			counter += ft_putchar_printf(arg_type[i], 1);
		i++;
	}
	va_end (args);
	return (counter);
}

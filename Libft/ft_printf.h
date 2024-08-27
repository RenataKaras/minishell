/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 15:35:03 by rkaras        #+#    #+#                 */
/*   Updated: 2024/02/06 16:39:07 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft.h"
# include <stdarg.h>

int	ft_printf(const char *arg_type, ...);
int	ft_pointhex(unsigned long n, char *hex);
int	ft_inthex(unsigned int n, char *format);
int	ft_putchar_printf(char c, int fd);
int	ft_putstr_printf(char *s, int fd);
int	ft_putnbr_printf(int n, int fd);
int	ft_itoa_printf(unsigned int n);

#endif
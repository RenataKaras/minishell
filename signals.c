/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/17 18:35:52 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/17 18:45:29 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//SIGQUIT is defined as 3 in signal.h
void	sigquit_handler(int num)
{
	(void)num;
	ft_putstr_fd("Quit (core dumped) :3\n", 1);
}


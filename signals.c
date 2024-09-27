/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/17 18:35:52 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/25 19:19:33 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//SIGQUIT is defined as 3 in signal.h
void	sigquit_handler(int num)
{
	(void)num;
	ft_putstr_fd("Quit (core dumped) :3\n", 1);
}

//term.c_lflag: "control local modes flag." in the termios struct
//contains various local modes for the terminal
//It controls settings related to input and output processing.
//ECHOCTL:a flag. When enabled, control characters (like Ctrl+C) are 
//echoed in a visible format (like ^C for Ctrl+C) when typed in the terminal
//~ECHOCTL: The ~ operator is a bitwise NOT operator that inverts 
//the bits of ECHOCTL.~ECHOCTL will clear it (turn it off).
//&=:The &= operator is a compound assignment that performs a bitwise AND
// operation and assigns the result back to term.c_lflag. 
//This operation effectively turns off the ECHOCTL flag.
//term.c_lflag &= ~ECHOCTL;the ECHOCTL flag in the terminal settings is desabled
//it means that control characters will not be echoed in the terminal.
//This can make the user experience cleaner, as control characters won't 
//be displayed in a visible form when they are typed.

void	init_signals(t_data *data)
{
	struct termios	terminal;

	terminal = data->original_terminal;
	terminal.c_lflag &= ~ECHOCTL;//may need to define?? or remove//or use ECHO only
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	data->heredoc_siginit = false;
	data->siginit_child = false;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

}


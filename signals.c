/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/17 18:35:52 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/27 18:01:33 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//SIGQUIT is defined as 3 in signal.h
void	sigquit_handler(int num)
{
	(void)num;
	//g_signal_number = num;
	ft_putstr_fd("Quit (core dumped) :3\n", 1);
}

static void	sigint_handler(int num)
{
		ft_putstr_fd("\n", 1);         // Print a newline when Ctrl+C is pressed.
    	rl_replace_line("", 0);        // Clear the current input line.
    	rl_on_new_line();              // Move to a new line (where the prompt goes).
    	rl_redisplay(); 				//redisplay prompt
		(void) num;
		g_signal_number = SIGINT;
}
//we will need to use it once we get children
//maybe keep the if block only putting the if when calling
void	process_sigint(t_data *data)
{
	// if (data->sigint_child)
	// {
	// 	puts("in if");
	// 	ft_putstr_fd("\n", 1);
	// 	data->sigint_child = false;
	// 	data->heredoc_siginit = true;
	// }
	// else
	(void) data;
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	//g_signal_number = 0;
}

//set sigint to false meaning no child process running

void	init_signals(t_data *data)
{
	struct termios	term;

	term = data->original_terminal;
	data->sigint_child = false;
	data->heredoc_siginit = false;
	signal(SIGINT, sigint_handler);
	// if (g_signal_number == SIGINT)//maybe here or from maintain prompt when have children
	// 	process_sigint(data);//This does not behave properly
	signal(SIGQUIT, SIG_IGN);
}


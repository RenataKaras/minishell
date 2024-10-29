/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/17 18:35:52 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/29 17:22:29 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ft_putstr_fd("\n", 1); Print a newline when Ctrl+C is pressed.
//rl_replace_line("", 0); Clear the current input line.
//rl_on_new_line();Move to a new line (where the prompt goes).
//rl_redisplay(); redisplay prompt

static void	parent_sigint_handler(int signum)
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void) signum;
}

static void	child_sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		(void) signum ;
	}
}

void	child_sigq_handler(int signum)
{
	if (signum == SIGQUIT)
		write(STDERR_FILENO, "Quit(core dumped)\n", 18);
}

void	heredoc_sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
	}
}

void	handle_signals(int process)
{
	if (process == PARENT)
	{
		signal(SIGINT, parent_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (process == CHILD)
	{
		signal(SIGINT, child_sigint_handler);
		signal(SIGQUIT, child_sigq_handler);
	}
	if (process == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}

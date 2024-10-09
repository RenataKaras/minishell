/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_heredoc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/27 20:41:31 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/09 16:23:50 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	heredoc_sigint_handler(int signum)
// {
// 	(void)signum;
// 	clean_minishell(data);//need to put it outside handler and send data
// 	exit(SIGINT);//also this cause otherwise program exits before exiting
// }

//'"' represents the double quote character.
//'\'' represents the single quote character.

bool	is_delimeter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	return (!*delimiter);
}

//input will hold the inputs of heredoc
//delm_str is a pointer to the delimeter str
//skip single and double quote chars within the delimeter
//in an infinite loop, use readline to wait for input
//if the input input matches value i.e. delimeter, we found delimeter, stop input
//if not found print the input to read or write end of pipe

//test if delm_str work instead of value

void	execute_heredoc(t_io_node *io, int pipefd[2], t_data *data)
{
	char	*input;
	char	*delm_str;

	//signal(SIGINT, heredoc_sigint_handler);
	delm_str = io->value;
	while (*delm_str && *delm_str == '"' && *delm_str == '\'')
		delm_str++;
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			break ;
		printf("see value : %s\n", delm_str);
		if (ft_strncmp(input, delm_str, ft_strlen(delm_str)) == 0)
		{
			puts("in here");
			break ;
		}
		puts ("what");
		if (!*delm_str)
			heredoc_expander(input, pipefd[1], data);
		else
		{
			ft_putstr_fd(input, pipefd[1]);
			ft_putchar_fd('\n', pipefd[1]);
		}
	}
	close(pipefd[1]);
	clean_minishell(data);
	exit(0);
}

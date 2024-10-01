/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_heredoc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/27 20:41:31 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/27 20:42:58 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_int_handler(int signum)
{
	(void)signum;
	clean_minishell();//need to put it outside handler and send data
	exit(SIGINT);//also this cause otherwise program exits before exiting
}

//'"' represents the double quote character.
//'\'' represents the single quote character.

bool	is_delimeter(char *delimeter, char *str)
{
	while (*str)
	{
		if (*delimeter == '"' || *delimeter == '\'')
		{
			delimeter++;
			continue ;
		}
		else if (*str == *delimeter)
		{
			str++;
			delimeter++;
		}
		else
			return (false);
	}
	while (*delimeter == '"' || *delimeter == '\'')
		delimeter++;
	if (*delimeter == '\0')
		return (true);
	else
		return (false);
}

//execute_heredoc implements heredoc funtionality
//line will hold the inputs of heredoc
//delm_str is a pointer to the delimeter str
//skip single and double quote chars within the delimeter
//in an infinite loop, use readline to wait for input
//if the input line matches value i.e. delimeter, we found delimeter, stop input
//if not found print the line to read or write end of pipe

void	execute_heredoc(t_io_node *io, int pipefd[2], t_data *data)
{
	char	*line;
	char	*delm_str;

	//signal(SIGINT, heredoc_int_handler);
	delm_str = io->value;
	while (*delm_str && *delm_str != '"' && *delm_str != '\'')
		delm_str++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_delimeter(io->value, line));//test if delm_str work instead of value
			break ;
		if (!*delm_str)//deal with it later
			ft_heredoc_expander(line, pipefd[1]);
		else
		{
			ft_putstr_fd(line, pipefd[1]);
			ft_putchar_fd("\n", pipefd[1]);
		}
		clean_minishell(data);
		exit(0);
	}
}
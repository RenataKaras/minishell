/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_heredoc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/27 20:41:31 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/28 15:25:21 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_delimeter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}

//For unquoted delimiters (EOF), the variables in input are expanded.
//$USER=rshaheen
//For quoted delimiters ("EOF"), the input is printed as-is.
//$USER=$USER

//input will hold the inputs of heredoc
//delm_str is a pointer to the delimeter str
//skip single and double quote chars within the delimeter
//in an infinite loop, use readline to wait for input
//if the input input matches value i.e. delimeter,we found delimeter,stop input
//if not found write the input to write end of pipe
//it will be stored in the read end of pipe
//test if delm_str work instead of value

void	execute_heredoc(t_io_node *io, int pipefd[2], t_data *data)
{
	char	*input;
	char	*delm_str;

	handle_signals(HEREDOC);
	delm_str = io->value;
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			break ;
		if (is_delimeter(io->value, input))
			break ;
		if (*delm_str == '"' || *delm_str == '\'')
		{
			ft_putstr_fd(input, pipefd[1]);
			ft_putchar_fd('\n', pipefd[1]);
		}
		else
			heredoc_expander(input, pipefd[1], data);
	}
	clean_minishell(data);
	exit (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 16:35:42 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/08/20 17:12:59 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	num_command(char *cmd_line)
{
	int	i;
	int	count;
	bool	has_double_quotes;
	
	i = 0;
	count = 1;
	has_double_quotes = false;
	while(cmd_line[i] != '\0')
	{
		if (cmd_line[i] == '"')
			has_double_quotes = !has_double_quotes;
		if ((cmd_line[i] == '|' || cmd_line[i] == '>' || cmd_line[i] == '<')
				&& has_double_quotes == false)
		{
			count+=2;
			if (cmd_line[i + 1] == '>' || cmd_line[i + 1] == '<')
				i++;
		} 
		i++;
	}
	return (count);
}

void split_cmd(t_data data)
{
	int	cmd_num;
	cmd_num = num_command(data.cmd_line);
	printf("%d\n", cmd_num);
}

void	cmd_parser(t_data *data)
{
	 split_cmd(*data);
}
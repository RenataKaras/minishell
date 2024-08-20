/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/19 16:56:22 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/20 16:17:24 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	cmd_before_operator(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd == '|')
		return (false);
	return (true);
}

bool	unclosed_quote(char *cmd)
{
	int		i;
	bool	single_q;
	bool	double_q;

	i = 0;
	single_q = false;
	double_q = false;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (cmd[i] == '"' && !single_q)
			double_q = !double_q;
		i++;
	}
	if (single_q == true || double_q == true)
		return (true);
	else
		return (false);
}

// void	input_checker(char *cmd)
// {
// 	int		i;
// 	char	operator;

// 	if (cmd_before_operator(cmd) == false)
// 		return (error_msg("Syntax error: operator before command"), false);
// 	if (unnclosed_quote(cmd) == true)
// 		return (error_msg("Syntax error: unclosed quotes"), false);
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
// 		{
// 			//cmd_after_operator
// 			operator = cmd[i];
// 			i++;
// 			//cmd_between_operators
// 		}
// 		i++;
// 	}
// 	//return (true);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/19 16:56:22 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/20 16:29:11 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	cmd_before_operator(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '|')
		return (false);
	return (true);
}

static bool	unclosed_quote(char *cmd)
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

static bool	cmd_after_operator(char *cmd, int i)
{
	if (cmd[i + 1] == '\0' || cmd[i + 1] == '|')
		return (false);
	if ((cmd[i] == '>' && cmd[i - 1] == '<')
		|| (cmd[i] == '<' && cmd[i - 1] == '>'))
		return (false);
	i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		return (false);
	return (true);
}

static bool	cmd_between_operators(char *cmd, int i, char operator)
{
	if ((operator == '>' && cmd[i] == '>')
		|| (operator == '<' && cmd[i] == '<'))
		i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (operator != '|' && (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<'))
		return (false);
	else if (operator == '|' && cmd[i] == '|')
		return (false);
	return (true);
}

bool	input_checker(char *cmd)
{
	int		i;
	char	operator;

	i = 0;
	if (cmd_before_operator(cmd) == false)
		return (error_msg("Syntax error: operator before command"), false);
	if (unclosed_quote(cmd) == true)
		return (error_msg("Syntax error: unclosed quotes"), false);
	while (cmd[i])
	{
		if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
		{
			if (cmd_after_operator(cmd, i) == false)
				return (error_msg("Syntax error: no command after operator"),
					false);
			operator = cmd[i];
			i++;
			if (cmd_between_operators(cmd, i, operator) == false)
				return (error_msg("Syntax error: no command between operators"),
					false);
		}
		i++;
	}
	return (true);
}

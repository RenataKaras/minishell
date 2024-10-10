/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/03 14:51:58 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/03 15:58:14 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	update_sign_and_index(char *str, int *i, int *sign)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

static int	exit_atoi(char *str, t_data *data)
{
	int					i;
	int					sign;
	int					exit_s;
	unsigned long long	result;

	i = 0;
	sign = 1;
	update_sign_and_index(str, &i, &sign);
	if (!is_number(str + i))
	{
		exit_s = display_err((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, str});
		(clean_minishell(data), exit(exit_s));
	}
	result = 0;
	while (str[i])
	{
		result = (result * 10) + (str[i] - '0');
		if (result > LONG_MAX)
		{
			exit_s = display_err((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, str});
			(clean_minishell(data), exit(exit_s));
		}
		i++;
	}
	return ((result * sign) % 256);
}


void	ft_exit(char **args, t_data *data)
{
	int	exit_status;

	exit_status = data->exit_status;
	if (args[1])
	{
		if (args[2] && is_number(args[1]))
		{
			exit_status = display_err(
					(t_err){ENO_GENERAL, ERRMSG_TOO_MANY_ARGS, NULL});
			(clean_minishell(data), exit(exit_status));
		}
		else
			exit_status = exit_atoi(args[1], data);
	}
	(clean_minishell(data), exit(exit_status));
}

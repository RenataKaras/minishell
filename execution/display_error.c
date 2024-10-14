/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display_error.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/01 17:12:37 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/03 15:55:32 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	display_err(t_err error)
{
	if (error.msg == ERRMSG_CMD_NOT_FOUND)
		return (ft_putstr_fd("minishelll: ", 2), ft_putstr_fd(error.source, 2),
			ft_putstr_fd(": command not found\n", 2), error.num);
	else if (error.msg == ERRMSG_NO_SUCH_FILE)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(error.source, 2),
			ft_putstr_fd(": No such file or directory\n", 2), error.num);
	else if (error.msg == ERRMSG_PERM_DENIED)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(error.source, 2),
			ft_putstr_fd(": Permission denied\n", 2), error.num);
	else if (error.msg == ERRMSG_AMBIGUOUS)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(error.source, 2),
			ft_putstr_fd(": ambiguous redirect\n", 2), error.num);
	else if (error.msg == ERRMSG_TOO_MANY_ARGS)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
			error.num);
	else if (error.msg == ERRMSG_NUMERIC_REQUI)
		return (ft_putstr_fd("minishell: exit: ", 2),
			ft_putstr_fd(error.source, 2),
			ft_putstr_fd(": numeric argument required\n", 2), error.num);
	return (0);
}

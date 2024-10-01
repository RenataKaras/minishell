/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_smpl_cmd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/01 16:07:35 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/01 20:14:48 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_stds(t_data *data, bool piped)
{
	if (piped)
		return ;
	dup2(data->stdin, 0);
	dup2(data->stdout, 1);
}

bool	is_builtin(char *arg)
{
	if (!arg)
		return (false);
	if (!ft_strcmp(arg, "echo")
		|| !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "exit")
		|| !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env"))
		return (true);
	return (false);
}
static int	exec_child(t_node *node, t_data *data)
{
	
}

int	exec_simple_cmd(t_data *data, bool piped)
{
	int	tmp_status;

	if (!data->ast->expanded_args)
	{
		tmp_status = exec_redirection(data->ast);
		return (reset_stds(data, piped), (tmp_status && ENO_GENERAL));
	}
	else if (is_builtin((data->ast->expanded_args)[0]))
	{
		tmp_status = exec_redirection(data->ast);
		if (tmp_status != ENO_SUCCESS)
			return (reset_stds(data, piped), ENO_GENERAL);
		tmp_status = ft_exec_builtin(data->ast->expanded_args, data);
		return (reset_stds(data, piped), tmp_status);
	}
	else
		return (exec_child(data->ast, data));
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_smpl_cmd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/01 16:07:35 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/08 17:46:45 by rshaheen      ########   odam.nl         */
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

t_path	get_path(char *cmd, t_data *data)
{
	char	*value;

	if (*cmd == '\0')
		return ((t_path){
			(t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, cmd}, NULL});
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return ((t_path){check_exec_perm(cmd, false), cmd});
	value = get_envlst_val("PATH", data->env);
	if (value)
		return (get_env_path(value, cmd));
	return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, cmd}, NULL});
}
//int execve(const char *pathname, char *const argv[], char *const envp[]);
//pathname: The path to the executable file you want to run.
//argv: An array of argument strings passed to the new program. 
//The first element should be the name of the program.
//envp: An array of environment variables for the new program.
//Return Value
//On success, execve does not return; the new program starts executing.
//On failure, it returns -1 and sets errno to indicate the error.

static int	exec_child(t_node *node, t_data *data)
{
	t_path	path_status;
	int		tmp_status;
	int		fork_pid;

	data->sigint_child = true;
	fork_pid = fork();
	if (!fork_pid)
	{
		tmp_status = exec_redirection(node);
		if (tmp_status != ENO_SUCCESS)
			(clean_minishell(data), exit(ENO_GENERAL));
		path_status = get_path((node->expanded_args)[0], data);
		if (path_status.error.num != ENO_SUCCESS)
		{
			tmp_status = msg_err(path_status.error);
			(clean_minishell(data), exit(tmp_status));
		}
		if (execve(path_status.path, node->expanded_args, data->envp) == -1)
			(clean_minishell(data), exit(1));
	}
	waitpid(fork_pid, &tmp_status, 0);
	data->sigint_child = false;
	return (get_exit_status(tmp_status));
}



//if no expanded args, it means redirection?
//first we execute rediections and reset std cause redirections change 
//stdin/stdout to files/pipes. reset to the original for future commands
//if it is a builtin we check and exec redirection for commands like
//echo "Hello" > file.txt and check the exit status of redirection
//if no rederection happened, (!= ENO_SUCCESS)
//we reset std even if no redirection happens or it fails
//If redirection was successful, the builtin is executed with redirection
//If redirection fails, ENO_GENERAL is returned right away, 
//and the builtin is not executed.
//if not a builtin, we execute_child??


int	exec_simple_cmd(t_data *data, bool piped, t_node *node)
{
	int	tmp_status;

	if (!node->expanded_args)
	{
		tmp_status = exec_redirection(node);
		return (reset_stds(data, piped), (tmp_status && ENO_GENERAL));
	}
	else if (is_builtin((node->expanded_args)[0]))
	{
		tmp_status = exec_redirection(node);
		if (tmp_status != ENO_SUCCESS)
			return (reset_stds(data, piped), ENO_GENERAL);
		tmp_status = exec_builtin(node->expanded_args, data);
		return (reset_stds(data, piped), tmp_status);
	}
	else
		return (exec_child(node, data));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/30 13:10:08 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/04 09:45:55 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_pipe_child(
	t_data *data, int pipefd[2], t_ast_direction dir, t_node *tree)
{
	int	status;

	if (dir == AST_LEFT)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else if (dir == AST_RIGHT)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	status = execute_node(tree, true, data);
	(clean_minishell(data), exit(status));
}

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static int	exec_pipe(t_data *data, t_node *tree)
{
	int	status;
	int	pipefd[2];
	int	pid_left;
	int	pid_right;

	data->sigint_child = true;
	pipe(pipefd);
	pid_left = fork();
	if (!pid_left)
		exec_pipe_child(data, pipefd, AST_LEFT, tree->left);
	else
	{
		pid_right = fork();
		if (!pid_right)
			exec_pipe_child(data, pipefd, AST_RIGHT, tree->right);
		else
		{
			(close(pipefd[0]), close(pipefd[1]));
			(waitpid(pid_left, &status, 0), waitpid(pid_right, &status, 0));
			data->sigint_child = false;
			return (get_exit_status(status));
		}
	}
	return (ENO_GENERAL);
}

int	execute_node(t_node *tree, bool piped, t_data *data)
{

	if (!tree)
		return (1);
	if (tree->type == N_PIPE)
		return (exec_pipe(data, tree));
	else
		return (exec_simple_cmd(data, piped));
	return (ENO_GENERAL);
}


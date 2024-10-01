/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/30 13:10:08 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/01 15:53:31 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_child(t_data *data, int pipefd[2], t_ast_direction dir)
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
	status = execute_node(data, true);
	(clean_minishell(data), exit(status));
}

static int	exec_pipeline(t_data *data)
{
	int	status;
	int	pipefd[2];
	int	pid_l;
	int	pid_r;

	data->sigint_child = true;
	pipe(pipefd);
	pid_l = fork();
	if (pid_l == 0)
		exec_child(data, pipefd, AST_LEFT);
}

int	execute_node(t_data *data, bool piped)
{
	int	status;

	if (!data->ast)
		return (1);
	if (data->ast->type == N_PIPE)
		return (exec_pipeline(data));
	else
		return (exec_simple_cmd(tree, piped));
	return (ENO_GENERAL);
}


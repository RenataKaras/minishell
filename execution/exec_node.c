/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_node.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/30 13:10:08 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/29 13:12:44 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//recursively keep calling execute_node
//until it turns into a simple command
//for left side we will write to pipe
//so we close the reading end pipefd[0]
//redirect stdout to write end
//then close the write end
//else we will read from the pipe
//so close the writing end
//redirect stdin to reading end
//then close it

static void	set_pipe_redir(
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
//WIFSIGNALED checks whether a child process terminated due to a signal
//by analyzing the exit status returned by wait or waitpid
//returns a non-zero value (true) if child process was terminated by a signal.
//WTERMSIG(status) returns the signal number that caused the child process to
//terminate if it was terminated by a signal
//Exit Status=128+Signal Number
//The value 128 is a constant used in the exit status encoding for processes
//that terminate due to signals. It allows for a clear distinction between 
//normal termination (exit codes 0-255) and 
//termination by signals (exit codes 128 + signal_number).
//WEXITSTATUS(status) extract the actual exit status (0 - 255)

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
//if (!pid_left) means if we're inside the left child (successful fork)
//else (means we are not inside left child)
//The else here ensures that the right fork happens "from" the parent
//and NOT from inside left child

static int	fork_for_pipe(t_data *data, t_node *tree)
{
	int	status;
	int	pipefd[2];
	int	pid_left;
	int	pid_right;

	data->sigint_child = true;
	pipe(pipefd);
	pid_left = fork();
	if (!pid_left)
		set_pipe_redir(data, pipefd, AST_LEFT, tree->left);
	else
	{
		pid_right = fork();
		if (!pid_right)
			set_pipe_redir(data, pipefd, AST_RIGHT, tree->right);
		else
		{
			(close(pipefd[0]), close(pipefd[1]),
				waitpid(pid_left, &status, 0), waitpid(pid_right, &status, 0));
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
	{
		return (fork_for_pipe(data, tree));
	}
	else
		return (exec_simple_cmd(data, piped, tree));
	return (ENO_GENERAL);
}

//Execution Flow for Pipe commands:
//Pipe Detected: execute_node() → fork_for_pipe()
//Fork Two Child Processes:
//Left child handles the left command.
//Right child handles the right command.
//Set up Pipe Redirection:
//Left child: Redirects STDOUT to the pipe.
//Right child: Redirects STDIN from the pipe.
//For Command Execution:
//Each child calls execute_node(), which eventually leads to 
//exec_simple_cmd() and execve() for the command on its side.
//Each command in the pipeline is executed in its respective child process.
//pipe commands get executed in the child processes created in fork_for_pipe(), 
//and execve() is called from within each child process after 
//redirections are set up,just like non-pipe commands. 
//The difference is that the pipe setup happens first, 
//before reaching the execve() call
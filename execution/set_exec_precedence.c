/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_exec_precedence.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/20 17:14:01 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/03 19:03:12 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// waitpid waits for a specific child process to change state (exit/ stop)
// prototype:
// pid_t waitpid(pid_t pid, int *status, int options);

// Parameters:
// pid: 
//   - The process ID of the child process to wait for. 
//   - Use -1 to wait for any child process.
//	here we are sendind a pointer though
// 
// status: 
//   - Pointer to an integer where the exit status of the child will be stored.
// 
// options: 
//   - Options for how to wait, usually set to 0 for default behavior.
// wait for child process to end, then make sigint false
//close write end of pipe
// Check if the child process exited normally and was terminated by SIGINT
//WIFEXITED checks if exited & WEXITSTATUS checks status

static bool	child_exit_normal(int pipefd[2], int *childpid, t_data *data)
{
	waitpid(*childpid, childpid, 0);
	signal(SIGQUIT, sigquit_handler);
	data->sigint_child = false;
	close (pipefd[1]);
	if (WIFEXITED(*childpid) && WEXITSTATUS(*childpid) == SIGINT)
		return (true);
	return (false);
}

//expansion refers to the process of interpreting and replacing certain chars
//with their corresponding values.
//when heredoc is found, we start ignoring SIGQUIT by SIG_IGN coz
//bash does not react to SIGQUIT inside heredoc
//execute_heredoc is only executed inside the child process(child_pid == 0)
//If the fork() fails (which would give a negative value to child_pid), 
//the execute_heredoc function will not be called,
//signal(SIGQUIT, SIG_IGN) might not be necessary, test later


//if args exist, they are expanded
//if heredoc detected, a child process is forked to handle the heredoc input, 
//which is written to a pipe.
//The read end of the pipe (pipefd[0])is stored in io->here_doc, 
//so the command can later read its input from the heredoc.
//Non-heredoc I/O are expanded and stored

static void	setup_io_and_heredoc(t_data *data)
{
	t_io_node	*io;
	int			pipefd[2];
	int			child_pid;

	if (data->ast->args)
		data->ast->expanded_args = expand(data);
	io = data->ast->io_list;
	while (io)
	{
		if (io->type == IO_HEREDOC)
		{
			pipe(pipefd);
			data->heredoc_siginit = true;
			child_pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (child_pid == 0)
				execute_heredoc(io, pipefd, data);
			if (child_exit_normal(pipefd, &child_pid, data))
				return ;
			io->here_doc = pipefd[0];
		}
		else
			io->expanded_value = expand(data);
		io = io->next;
	}
}

//The left subtree represents the command before the pipe
//the right subtree represents the command after the pipe.

//if we detect pipe we call the function recursively with left node of AST
//by recursion, we keep moving left until we reach the leftmost node
//we call the setup_io_and_heredoc on it cause recursion will break 
//when it finds no more pipe
//we want the command BEFORE the pipe (leftmost) to be processed first
//because BASH does it

//when we have NO more left nodes to process, we check--
//if data->heredoc_siginit is false, means no heredoc is active
//we recursively call the function on the right subtree (node->right).
//until we reach the right most node
//then call setup_io_and_heredoc on it

// Precedence is established by processing the left command first,
// then the right command only if no heredoc is detected.

//if a heredoc is encountered in the left subtree, 
//the right command will not execute until the heredoc is processed by setup_io


void	set_exec_precedence(t_node *node, t_data *data)
{
	if (!node)
		return ;
	if (node->type == N_PIPE)
	{
		set_exec_precedence(node -> left, data);
		if (!data->heredoc_siginit)
			set_exec_precedence(node -> right, data);
	}
	else
		setup_io_and_heredoc(data);
}


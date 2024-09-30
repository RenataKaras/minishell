/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_tree.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/20 17:14:01 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/30 12:34:38 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	init_leaf(t_data *data)
{
	t_io_node	*io;
	int			pipefd[2];
	int			child_pid;

	if (data->ast->args)
		data->ast->expanded_args = ft_expand(data->ast->args);
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
			io->here_doc = pipefd[0];//why
		}
		else
			io->expanded_value = ft_expand();
		io = io->next;
	}
}

//Pipes (|) are processed left-to-right (send output from left to right).
//Heredoc (<<) typically applies to the right-hand command,
//cmd1 | cmd2 << heredoc, here, cmd1 writes its output to cmd2 by the pipe.
//and The heredoc provides data to cmd2
//In (AST), cmd1 is on the left side of the tree (because it's executed first)
//and cmd2 is on the right (because it receives data from cmd1)
//When there's heredoc, it affects the right side (i.e., cmd2).
//So the tree processes the right-hand side when the heredoc isn't initialized
//meaning data->heredoc_sigint is false-meaning not ready to process heredoc
//to ensure that cmd2 properly receives input from the heredoc 
//INSTEAD OF from cmd1's pipe, we set it to right
//while it’s not mandatory to place the command affected by heredoc on the right
//the design conventionally puts it there for consistency with other operators.


void	init_tree(t_data *data)
{
	if (!data->ast)
		return ;
	if (data->ast->type == N_PIPE)
	{
		init_tree(data ->ast -> left);
		if (!data->heredoc_siginit)
			init_tree(data-> ast -> right);
	}
	else
		init_leaf(data);
}

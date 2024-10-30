/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_redirec.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/01 16:22:40 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/30 14:20:53 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//the output redirections can only specify one file
//so second variable, depicted by [1]is invalid for output redirection
//display_error generates an error message based on the error type 
//and returns the corresponding error number, which is stored in 'exit_status'
// io_list->value holds the filename or path for the redirection,
// which is passed as char *source to the t_err struct for error reporting.
//example output- minishell: output.txt: ambiguous redirect
//here error.source was output.txt
//Return the error stored in exit_status
//open return -1 on failure
//if write permission is a yes, it returns t_err with ENO_SUCCESS, which cannot
//invoke any of the if's in display_error function and returns 0.

int	set_output_redir(t_io_node *io_list, int *exit_status)
{
	int	fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*exit_status = show_err(
				(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
		return (*exit_status);
	}
	fd = open(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		*exit_status
			= show_err(check_write_perm(io_list->expanded_value[0]));
		return (*exit_status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*exit_status = 0;
	return (*exit_status);
}

int	set_input_redir(t_io_node *io_list, int *exit_status)
{
	int	fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*exit_status = show_err(
				(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
		return (*exit_status);
	}
	fd = open(io_list->expanded_value[0], O_RDONLY);
	if (fd == -1)
	{
		*exit_status
			= show_err(check_read_perm(io_list->expanded_value[0]));
		return (*exit_status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*exit_status = 0;
	return (*exit_status);
}

int	set_append_redir(t_io_node *io_list, int *exit_status)
{
	int	fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*exit_status = show_err(
				(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
		return (*exit_status);
	}
	fd = open(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*exit_status
			= show_err(check_write_perm(io_list->expanded_value[0]));
		return (*exit_status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*exit_status = 0;
	return (0);
}

int	exec_redirection(t_node *node)
{
	t_io_node	*tmp_io;
	int			tmp_status;

	tmp_io = node->io_list;
	while (tmp_io)
	{
		if (tmp_io->type == IO_OUT
			&& set_output_redir(tmp_io, &tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_IN
			&& set_input_redir(tmp_io, &tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_APPEND
			&& set_append_redir(tmp_io, &tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_HEREDOC)
			(dup2(tmp_io->here_doc, 0), close(tmp_io->here_doc));
		tmp_io = tmp_io->next;
	}
	return (ENO_SUCCESS);
}

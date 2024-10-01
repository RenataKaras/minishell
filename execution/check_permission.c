/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_permission.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/01 18:16:46 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/01 18:40:20 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//checks the first char of the str is null by *file
// file can be a filename or path to that file
//path can be a char *str like
//char *filePath = "/home/user/documents/file.txt";  // Absolute path
// t_err error.msg is 42, could be success or whatever

t_err	check_exec_perm(char *file, bool cmd)
{
	if (!*file)
		return ((t_err){ENO_GENERAL, ERRMSG_NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == -1)
			return ((t_err){ENO_CANT_EXEC, ERRMSG_PERM_DENIED, file});
		return ((t_err){ENO_SUCCESS, 42, NULL});
	}
	if (cmd)
		return ((t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, file});
	return ((t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, file});
}

t_err	check_read_perm(char *file)
{
	if (!*file)
		return ((t_err){ENO_GENERAL, ERRMSG_NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK) == -1)
			return ((t_err){ENO_GENERAL, ERRMSG_PERM_DENIED, file});
		return ((t_err){ENO_SUCCESS, 42, NULL});
	}
	return ((t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, file});
}

t_err	check_write_perm(char *file)
{
	if (!*file)
		return ((t_err){ENO_GENERAL, ERRMSG_NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return ((t_err){ENO_GENERAL, ERRMSG_PERM_DENIED, file});
		return ((t_err){ENO_SUCCESS, 42, NULL});
	}
	return ((t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, file});
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 15:51:48 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/30 15:01:14 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//getcwd function in C retrieves the current working directory
//char *getcwd(char *buf, size_t size);
//Parameters:
//*buf (char ):
//it's a pointer to a buffer where the current working directory will be stored.
//if passed NULL, getcwd will allocate memory for cwd name.
//size (size_t):
//This specifies the size of the buffer (buf) you are passing.
//If passed 0, it tells getcwd to allocate enough memory for the path

int	ft_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	return (0);
}

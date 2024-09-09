/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/04 17:58:03 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/09 15:54:48 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *key)
{
	t_env	*envlst;

	envlst = g_minishell.env_link_list;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}
/*
* ft_cd_home changes the current working directory to user's home directory.
* int chdir(const char *dir_name);
* chdir is a standard C lib function that changes the current working directory
* of the CALLING process to the directory specified by the PATH provided.
* returns 0 on success and -1 in failure
* This function records the PWD in OLDPWD
* Then it gets the value of HOME and
* changes the PWD to HOME
*/

static int	ft_cd_home(void)
{
	char	*home;

	update_val_make_node("OLDPWD", get_env_value("PWD"), false);
	home = get_env_value("HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == ENO_SUCCESS)
		return (update_val_make_node("PWD", home, false), 0);
	return (1);
}

static int	cd_err_msg(char *dir_name)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(dir_name, 2);
	ft_putstr_fd("':no such file or directory\n", 2);
	return (1);
}

static int	change_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	return (update_val_make_node("PWD", cwd, false), 0);
}

int	ft_cd(char *dir_name)
{
	if (!dir_name)
		return (ft_cd_home());
	if (chdir(dir_name) != ENO_SUCCESS)
		return (cd_err_msg(dir_name));
	update_val_make_node("OLDPWD", get_env_value("PWD"), false);
	return (change_pwd());
}


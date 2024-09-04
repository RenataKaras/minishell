/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/04 17:58:03 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/04 18:39:55 by rshaheen      ########   odam.nl         */
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
/**/
static int	ft_cd_home(void)
{
	char	*home;

	set_val_make_node("OLDPWD", get_env_value("PWD"), false);
	home = get_env_value("HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == ENO_SUCCESS)
		return (set_val_make_node("PWD", home, false), 0);
	return (1);
}

int	ft_cd(char *path)
{
	if (!path)
		return (ft_cd_home);
}
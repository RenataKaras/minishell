/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_envp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 16:22:22 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/08/28 18:15:14 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *str)
{
	size_t	i;

	i = 0;

	while (str[i])
	{
		if (str[i] == '=')
			return (free_or_add_list(ft_substr(str, 0, i), false));
		i++;
	}
	return (ft_strdup(str));
}

//what happens if substring fails???????
//if = is found, make substr without the =
//if = is not found, return the string

char	*extract_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (free_or_add_list(
					ft_substr(str, i, ft_strlen(str) - i), false));
		}
		i++;
	}
	return (NULL);
}

//if = not found, return NULL
//what happens if substring fails???????

void	update_list(char *key, char *value, bool create)
{
	t_env	*envlst;

	envlst = g_minishell.env_link_list;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
		{
			if (value)
				envlst->value = 
		}
	}

}


void	copy_envp(void)
{
	int		i;
	char	**original_env;
	char	*key;
	char	*value;

	original_env = g_minishell.env;
	if (!original_env)
		return ;
	i = 0;
	while (original_env[i])
	{
		key = extract_key(original_env[i]);
		value = extract_value(original_env[i]);
		update_list(key, value, true);
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_env_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 17:46:23 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/15 16:47:06 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_key(char *str)
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

char	*copy_value(char *str)
{
	size_t	i;
	char	*substr;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			substr = ft_substr(str, i, ft_strlen(str) - i);
			if (!substr)
				return (NULL);
			return (free_or_add_list(substr, false));
		}
		i++;
	}
	return (NULL);
}

//if = not found, return NULL
//what happens if substring fails???????

void	make_env_list(t_data *minishell)
{
	int		i;
	char	**original_env;
	char	*key;
	char	*value;

	original_env = minishell->envp;
	if (!original_env)
		return ;
	i = 0;
	while (original_env[i])
	{
		key = copy_key(original_env[i]);
		//printf("key:%s\n", key);
		value = copy_value(original_env[i]);
		//printf("value:%s\n", value);
		update_val(minishell, key, value, true);
		i++;
	}
}

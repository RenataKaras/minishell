/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_env_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 17:46:23 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/15 16:52:21 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_key(char *str)
{
	size_t	i;
	char	*substr;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			substr = ft_substr(str, 0, i);
			if (!substr)
				return (NULL);
			return (free_or_add_list(substr, false));
		}
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
		value = copy_value(original_env[i]);
		update_val(minishell, key, value, true);
		i++;
	}
}

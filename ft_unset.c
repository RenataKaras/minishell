/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/19 16:16:50 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/08/19 18:25:54 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_envls *previous, t_envls *current, t_envls **env)
{
	t_envls	*tmp;

	if (previous == NULL)
		*env = current->next;
	else
		previous->next = current->next;
	tmp = current;
	current = current->next;
	free(tmp->keyword);
	free(tmp->info);
	free(tmp);
}

void	ft_unset(t_envls **envls, char *command)
{
	char	*str;
	t_envls	*previous;
	t_envls	*current;
	size_t	key_len;

	previous = NULL;
	current = *envls;
	if (&command[1] == NULL)
		return ;
	key_len = ft_strlen(&command[1]);
	str = (char *)ft_calloc(key_len + 2, sizeof(char));
	if (str == NULL)
		return ;
	ft_strlcpy(str, &command[1], key_len + 1);
	str[key_len] = '=';
	while (current != NULL)
	{
		if (ft_strncmp(current->keyword, str, key_len + 1) == 0)
		{
			delete_node(previous, current, envls);
			free(str);
			return ;
		}
		previous = current;
		current = current->next;
	}
	free(str);
}

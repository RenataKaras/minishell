/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 14:47:33 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/08/20 14:47:55 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envls	*new_node(char *env)
{
	t_envls	*envls;//pointer to the new node
	char	*temp;// Temporary string to hold the trimmed environment value.
	int		i;// Index to find the position of the '=' character in the envp string.

	envls = malloc(sizeof(t_envls));//for new node
	if (!envls)
		return (NULL);//error message
	i = 0;
	while (env[i] != '=' && env[i])//find the position of = 
		i++;
	envls->keyword = ft_calloc(sizeof(char), i + 2);//allocate memory for key
	if (!envls->keyword)
		return (free(envls), NULL);//error message & free
	ft_strlcpy(envls->keyword, env, (i + 2));//copy the key part
	temp = ft_strtrim(env, envls->keyword);//trim the key to get the value part
	envls->info = ft_strdup(temp);//copy the value part into info
	free(temp);
	envls->next = NULL;
	return (envls);
}

static void	lstadd_back(t_envls **head, void *content)
{
	t_envls	*current_node;
	t_envls	*new;

	current_node = *head;
	while (current_node->next != NULL)
		current_node = current_node->next;
	new = new_node(content);
	current_node->next = new;
}

t_envls	*copy_env(char **env)
{
	t_envls	*env_lst;//pointer to the head of list
	int		i;

	env_lst = new_node(env[0]);//create the head from the first envp element
	if (!env_lst)
		return (NULL);
	i = 1;
	while (env[i])//loop through the rest and keep adding them as nodes
	{
		lstadd_back(&env_lst, env[i]);
		i++;
	}
	return (env_lst);//return the head
}

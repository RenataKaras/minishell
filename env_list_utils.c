/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshaheen <rshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:47:05 by rshaheen          #+#    #+#             */
/*   Updated: 2024/09/09 16:09:20 by rshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// If g_minishell.env_link_list has not been initialized
// set the new node as the head
// If it is already initialized, traverse to the end of the list
// Then Append the new node to the end of the list
void	append_new_node(t_env *new)
{
	t_env	*current;

	if (!g_minishell.env_link_list)
	{
		g_minishell.env_link_list = new;
		return ;
	}
	current = g_minishell.env_link_list;
	while (current && current->next)
		current = current->next;
	current->next = new;
}

t_env	*create_new_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = free_or_add_list(ft_strdup(key), false);
	if (value)
		new->value = free_or_add_list(ft_strdup(value), false);
	new->next = NULL;
	return (new);
}

void	update_val_make_node(char *key, char *value, bool make)
{
	t_env	*envlst;

	envlst = g_minishell.env_link_list;
	while (envlst)
	{
		if (ft_strcmp(key, envlst->key) == 0)
		{
			if (value)
				envlst->value = free_or_add_list(ft_strdup(value), false);
			return ;
		}
		envlst = envlst->next;
	}
	if (make)
		append_new_node(create_new_node(key, value));
}
/*
 * On the very first call of this function from make_env_list:
 * `g_minishell.env_link_list` will be NULL cause it hasn't been initialized yet.
 * so, `envlst` will be NULL, and the function will not enter the while loop.
 * The function will make a new node and use append_new_node to initialize.
 *
 * So
 * On subsequent calls,it will not be empty
 * 
 * On subsequent calls:
 *
 * 1. Traverse the list to find a node with the matching key.
 *
 * 2. If the key exists:
 *    - If value is not NULL, update the existing node's value with it
 *    - If value is NULL, do nothing to the existing node's value.
 *
 * 3. If the key does not exist:
 *    - If make is true, make a new node with the key and value,
 *      and add it to the end of the list.
 *    - If make is false, do nothing; no new node is created, and
 *      the list remains unchanged.
 */
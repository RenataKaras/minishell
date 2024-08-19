/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/19 15:50:11 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envls	*new_node(char *env)
{
	t_envls	*envls;
	char	*temp;
	int		i;

	envls = malloc(sizeof(t_envls));
	if (!envls)
		return (NULL);//error message
	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	envls->keyword = ft_calloc(sizeof(char), i + 2);
	if (!envls->keyword)
		return (free(envls), NULL);//error message & free
	ft_strlcpy(envls->keyword, env, (i + 2));
	temp = ft_strtrim(env, envls->keyword);
	envls->info = ft_strdup(temp);
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
	t_envls	*env_lst;
	int		i;

	env_lst = new_node(env[0]);
	if (!env_lst)
		return (NULL);
	i = 1;
	while (env[i])
	{
		lstadd_back(&env_lst, env[i]);
		i++;
	}
	return (env_lst);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;

	// if (argc != 1 && argv)
		//eror messages
	data.envp = envp;
	data.env = copy_env(data.envp);
	return (0);
}

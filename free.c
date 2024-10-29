/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 17:19:27 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/29 17:16:39 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array, int i)
{
	if (!array)
		return ;
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

static void	clear_envlst(t_data *data)
{
	t_envls	*envlst;
	t_envls	*envlst_tofree;

	envlst = data->env;
	while (envlst)
	{
		envlst_tofree = envlst;
		envlst = envlst->next;
		free(envlst_tofree);
	}
	data->env = NULL;
}

static void	free_pointer(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	*free_or_add_list(void *ptr, bool clean)
{
	static t_list	*node_collection;

	if (clean)
	{
		ft_lstclear(&node_collection, free_pointer);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&node_collection, ft_lstnew(ptr));
		return (ptr);
	}
}
//node_collection RETAINS it's state between function calls cause its STATIC. 
//It accumulates nodes when clean is false and clears them when clean is true.
//false: Adds the given pointer to node_collection and returns it future use.

void	clean_minishell(t_data *data)
{
	free_or_add_list(NULL, true);
	clear_ast(&data->ast, data->token_list);
	clear_envlst(data);
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &data->original_terminal);
}

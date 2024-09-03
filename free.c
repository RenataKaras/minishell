/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 17:19:27 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/03 17:06:40 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

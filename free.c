/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 17:19:27 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/08/28 17:45:57 by rshaheen      ########   odam.nl         */
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
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, free_pointer);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
		return (ptr);
	}
}
//if clean is true: Triggers the cleanup process
//by clearing all items from garbage_list and freeing their memory.
//clean is false: Adds the given pointer to garbage_list for future cleanup.

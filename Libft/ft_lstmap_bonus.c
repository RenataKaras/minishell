/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 17:54:29 by rkaras        #+#    #+#                 */
/*   Updated: 2024/02/06 17:11:40 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*pointer;
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst != NULL)
	{
		pointer = f(lst->content);
		new_node = ft_lstnew(pointer);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			del(pointer);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

//iterates the list 'lst' and applies the function 'f' on the content
//of each node. Creates a new list resulting of the successive applications
//of the function 'f'. the 'del' function is used to delete the content
//of the node if needed.
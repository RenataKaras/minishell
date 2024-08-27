/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 17:58:45 by rkaras        #+#    #+#                 */
/*   Updated: 2024/02/06 16:55:27 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(1 * sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}

// int		main(void)
// {
// 	char	str[] = "all hail bulbasaur";

// 	t_list	*new;

// 	new = ft_lstnew(str);
// 	printf("\n%s\n", (char*)new->content);
// }

//creates a new node and allocates memory for it

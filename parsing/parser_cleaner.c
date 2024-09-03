/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_cleaner.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 15:06:49 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/03 15:21:13 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_char2(char **str)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	clear_io_list(t_io_node **lst)
{
	t_io_node	*current;
	t_io_node	*next;

	current = *lst;
	while (current)
	{
		free(current->value);
		free_char2(current->expanded_value);
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	clear_cmd_node(t_node *node)
{
	if (!node)
		return ;
	clear_io_list(&(node->io_list));
	free(node->args);
	free_char2(node ->expanded_args);
}

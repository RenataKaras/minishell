/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_lists.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 15:48:00 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/18 16:34:58 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_io_type	get_io_type(t_token_type redir_type)
{
	if (redir_type == T_LESS)
		return (IO_IN);
	else if (redir_type == T_GREAT)
		return (IO_OUT);
	else if (redir_type == T_DLESS)
		return (IO_HEREDOC);
	else
		return (IO_APPEND);
}

t_node	*new_parse_node(t_node_type type)
{
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

t_io_node	*new_io_node(t_token_type redir_type, char *value)
{
	t_io_node	*new_node;

	new_node = (t_io_node *)ft_calloc(1, sizeof(t_io_node));
	if (!new_node)
		return (NULL);
	new_node->type = get_io_type(redir_type);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (free(new_node), NULL);
	return (new_node);
}

void	append_io_node(t_io_node **lst, t_io_node *new)
{
	t_io_node	*current;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current && current->next)
		current = current->next;
	current->next = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 16:29:35 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/12 17:07:03 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_prec(t_token_type type)
{
	if (type == T_AND)
		return (0);
	return (1);
}

bool	curr_token_is_binop(t_token *token_list)
{
	if (!token_list)
		return (false);
	if (token_list->type == T_PIPE || token_list->type == T_AND)
		return (true);
	return (false);
}

void	get_next_token(t_token **token_list)
{
	*token_list = (*token_list)->next;
}

bool	is_redirection(t_token_type type)
{
	if (type == T_DGREAT || type == T_DLESS
		|| type == T_LESS || type == T_GREAT)
		return (true);
	return (false);
}

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

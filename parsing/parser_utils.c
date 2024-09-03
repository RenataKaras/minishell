/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 16:29:35 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/03 17:46:19 by rkaras        ########   odam.nl         */
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

char	*ft_strjoin_with(char const *s1, char const *s2, char sep)
{
	size_t	totals;
	char	*newstring;

	totals = ft_strlen(s1) + ft_strlen(s2) + 2;
	newstring = (char *) malloc (totals * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	ft_strlcpy(newstring, s1, ft_strlen(s1) + 1);
	newstring[ft_strlen(s1)] = sep;
	ft_strlcpy(newstring + ft_strlen(s1) + 1, s2, ft_strlen(s2) + 1);
	return (newstring);
}

bool	curr_token_is_binop(t_token *token_list)
{
	if (!token_list)
		return (false);
	if (token_list->type == T_PIPE || token_list->type == T_AND
		|| token_list->type == T_OR)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 16:29:35 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/22 12:03:07 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_with(char const *s1, char const *s2, char sep)
{
	size_t	totals;
	char	*newstring;

	if (!s1 || !s2)
		return (NULL);
	if (!sep || !ft_strlen(s1) || !ft_strlen(s2))
		return (ft_strjoin(s1, s2));
	totals = ft_strlen(s1) + ft_strlen(s2) + 2;
	newstring = (char *) malloc (totals * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	ft_strlcpy(newstring, s1, ft_strlen(s1) + 1);
	newstring[ft_strlen(s1)] = sep;
	ft_strlcpy(newstring + ft_strlen(s1) + 1, s2, ft_strlen(s2) + 1);
	return (newstring);
}

void	get_next_token(t_token **token_list)
{
	if (token_list && *token_list)
		*token_list = (*token_list)->next;
	else
		return ;
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

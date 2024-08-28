/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizing_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 17:39:08 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/26 18:23:23 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	else
		return (false);
}

void	skip_spaces(char **line)
{
	while (**line && is_space(**line))
		(*line)++;
}


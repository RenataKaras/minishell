/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 15:54:14 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/16 14:50:18 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_data *minishell)
{
	t_envls	*list;

	list = minishell->env;
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (ENO_SUCCESS);
}

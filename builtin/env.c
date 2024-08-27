/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 15:54:14 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/08/27 16:54:04 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(void)
{
	t_env	*list;

	list = g_minishell.envlst;
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (ENO_SUCCESS);
}

//The ft_env function works with the list that is obtained from 
// the g_minishell.envlst. 
//This envlst is part of the global g_minishell struct, 
//which contains the environment variables for minishell.

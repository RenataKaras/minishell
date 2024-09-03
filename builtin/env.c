/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 15:54:14 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/03 18:17:39 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(void)
{
	t_env	*list;

	list = g_minishell.env_link_list;
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (EXIT_SUCCESS);
}
// Use ENO_SUCCESS is part of the custom enum e_err_no
// it indicates function executed successfully.
// This is used for consistent error handling throughout the codebase.


//The ft_env function works with the list that is obtained from 
// the g_minishell.env_link_list. 
//This is part of the global g_minishell struct, 
//which contains the environment variables for minishell.


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/19 16:44:06 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_env_list(t_envls *head)
// {
//     t_envls *current = head;

//     while (current != NULL)
//     {
//         printf("Keyword: %s, Info: %s\n", current->keyword, current->info);
//         current = current->next;
//     }
// }

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;

	// if (argc != 1 && argv)
		//eror messages
	data.envp = envp;
	data.env = copy_env(data.envp);
	// print_env_list(data.env);
	return (0);
}

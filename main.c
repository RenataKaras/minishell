/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/30 14:43:07 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_env_list(t_token *head)
// {
//     t_token *current = head;

//     while (current != NULL)
//     {
//         printf("Type: %u, Value: %s\n", current->type, current->value);
//         current = current->next;
//     }
// }

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}

void	maintain_prompt(t_data data)
{
	t_token	*token_list;

	while (1)
	{
		data.cmd_line = readline("minishell> ");
		add_history(data.cmd_line);
		// input_checker(data.cmd_line);
		token_list = tokenize(data.cmd_line);
		parse (token_list);
		// print_env_list (token_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;

	if (argc != 1 && argv)
		return (error_msg("Wrong number of arguments"), EXIT_FAILURE);
	data.envp = envp;
	data.env = copy_env(data.envp);
	// print_env_list(data.env);
	maintain_prompt(data);
	return (0);
}

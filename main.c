/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 17:53:47 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/30 14:18:11 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}

static void	init_minishell(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->envp = envp;
	make_env_list(data);
	data->stdin = dup(0);
	data->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &data->original_terminal);
}

static void	start_execution(t_data *data)
{
	signal(SIGQUIT, child_sigq_handler);
	set_exec_precedence(data->ast, data);
	if (data->heredoc_siginit)
		data->heredoc_siginit = false;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->original_terminal);
	data->exit_status = execute_node(data->ast, false, data);
	clear_ast(&data->ast, data->token_list);
}

void	*maintain_prompt(t_data *data)
{
	while (1)
	{
		handle_signals(PARENT);
		data->cmd_line = readline("minishell> ");
		if (!data->cmd_line)
		{
			ft_putstr_fd("exit\n", 1),
			close(data->stdin);
			close(data->stdout);
			exit(data->exit_status);
		}
		if (data->cmd_line[0])
			add_history(data->cmd_line);
		data->token_list = tokenize(data->cmd_line);
		if (!data->token_list)
			continue ;
		data->ast = parse(data->token_list, data);
		if (data->parse_error == true)
		{
			handle_parse_error(data);
			continue ;
		}
		start_execution(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	if (argc != 1 || argv[1])
		return (error_msg("Wrong number of arguments"), EXIT_FAILURE);
	init_minishell(&data, envp);
	maintain_prompt(&data);
	free_or_add_list(NULL, true);
	clean_minishell(&data);
	return (data.exit_status);
}

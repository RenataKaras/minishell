/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 17:52:07 by rkaras        #+#    #+#                 */
/*   Updated: 2024/08/26 18:23:42 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Libft/libft.h"
# include "./Libft/ft_printf.h"
# include "./Libft/get_next_line.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_AND,
	T_OR,
	T_NL,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_envls
{
	char			*keyword;
	char			*info;
	struct s_envls	*next;
}					t_envls;

typedef struct s_data
{
	char	*cmd_line;
	char	**cmd_table;
	char	**path;
	char	**envp;
	t_envls	*env;
}			t_data;

//parsing
t_envls	*copy_env(char **env);
// bool	input_checker(char *cmd);
void	tokenize(char *cmd_line);
bool	is_space(char c);
int		skip_spaces(char **line);



//error handling
void	error_msg(char *msg);

#endif
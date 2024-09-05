/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 17:52:07 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/05 18:41:38 by rkaras        ########   odam.nl         */
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

//tokenizing structs
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

//*A*bstract *S*yntax *T*ree structs
typedef enum e_node_type
{
	N_PIPE,
	N_AND,
	N_OR,
	N_CMD
}	t_node_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef struct s_io_node
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					here_doc;
	struct s_io_node	*prev;
	struct s_io_node	*next;
}	t_io_node;

typedef struct s_node
{
	t_node_type		type;
	t_io_node		*io_list;
	char			*args;
	char			**expanded_args;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

//environment linked list
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

// extern t_data g_data;

/*PARSING*/
//parser_cleaner
void		clear_io_list(t_io_node **lst);
void		clear_cmd_node(t_node *node);
void		free_char2(char **str);

//parser_helpers
bool		join_args(char **args, t_token *token_list);
bool		get_io_list(t_io_node **io_list, t_token *token_list);
t_node		*get_simple_cmd(t_token *token_list);

//parser_lists
t_node		*new_parse_node(t_node_type type);
t_io_node	*new_io_node(t_token_type redir_type, char *value);
void		append_io_node(t_io_node **lst, t_io_node *new);

//parser_utils
t_io_type	get_io_type(t_token_type redir_type);
char		*ft_strjoin_with(char const *s1, char const *s2, char sep);
bool		curr_token_is_binop(t_token *token_list);
void		get_next_token(t_token **token_list);
bool		is_redirection(t_token_type type);

//parser
t_node		*term(t_token *token_list);
t_node		*expression(int min_prec, t_token *token_list);
void		parse(t_token *token_list);

t_envls		*copy_env(char **env);

// bool	input_checker(char *cmd);

//tokenizing
t_token		*tokenize(char *cmd_line);
bool		is_space(char c);
void		skip_spaces(char **line);
t_token		*tokenization(char *cmd_line);
int			handle_separator(char **line_ptr, t_token **token_list);
int			add_separator(t_token_type type, char **line_ptr,
				t_token **token_list);
t_token		*new_token_node(char *value, t_token_type type);
void		token_lst_add_back(t_token **token_list, t_token *new_token);
int			add_identifier(char **line_ptr, t_token **token_list);
bool		is_separator(char *s);
bool		is_quote(char c);
bool		skip_quotes(char *line, int *i);
void		free_token_list(t_token **token_list);

//error handling
void		error_msg(char *msg);

#endif
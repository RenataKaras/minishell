/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 17:52:07 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/18 16:36:11 by rkaras        ########   odam.nl         */
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
	T_AND,
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

//general struct
typedef struct s_data
{
	char	*cmd_line;
	t_token	*token_list;
	t_node	*ast;
	char	**envp;
	t_envls	*env;
}			t_data;


void		print_env_list(t_token *head);

/*PARSING*/

//parser_cleaner
void		clear_ast(t_node **ast, t_token *token_list);
void		clear_ast_nodes(t_node **left, t_node **right, t_token *token_list);
void		clear_io_list(t_io_node **lst);
void		clear_cmd_node(t_node *node);
void		recursively_clear_ast(t_node *node);

//parser_helpers
bool		get_io_list(t_io_node **io_list, t_token *token_list);
t_node		*get_simple_cmd(t_token *token_list);
bool		join_args(char **args, t_token **token_list);

//parser_lists
void		append_io_node(t_io_node **lst, t_io_node *new);
t_io_type	get_io_type(t_token_type redir_type);
t_io_node	*new_io_node(t_token_type redir_type, char *value);
t_node		*new_parse_node(t_node_type type);

//parser_utils
char		*ft_strjoin_with(char const *s1, char const *s2, char sep);
void		free_char2(char **str);
void		get_next_token(t_token **token_list);
bool		is_redirection(t_token_type type);

//parser
t_node		*combine(t_node *left, t_node *right);
t_node		*expression(int min_prec, t_token **token_list);
t_node		*handle_term_and_token(t_token **token_list);
t_node		*parse(t_token *token_list);
t_node		*term(t_token *token_list);


t_envls		*copy_env(char **env);

/*TOKENIZING*/

//token_adder
int			add_identifier(char **line_ptr, t_token **token_list);
int			add_separator(t_token_type type, char **line_ptr,
				t_token **token_list);

//token_list
void		free_token_list(t_token **token_list);
t_token		*new_token_node(char *value, t_token_type type);
void		token_lst_add_back(t_token **token_list, t_token *new_token);

//tokenize
int			handle_separator(char **line_ptr, t_token **token_list);
t_token		*tokenization(char *cmd_line);
t_token		*tokenize(char *cmd_line);

//tokenizing utils
bool		is_separator(char *s);
bool		is_space(char c);
bool		is_quote(char c);
void		skip_spaces(char **line);
bool		skip_quotes(char *line, int *i);

//error handling
void		error_msg(char *msg);

#endif
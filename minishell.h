/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 17:52:07 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/24 16:23:02 by rshaheen      ########   odam.nl         */
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
# include <termios.h>

/*
 * Enumeration, or enum, is a user-defined data type in C/other languages 
 * that consists of a set of named integer constants. 
 * It allows you to assign names to a series of related integer values, 
 * making the code more readable and maintainable.
 * Here, The enum is used to standardize error
 * handling throughout the program by using descriptive names instead of
 * raw numbers.
 */
//tokenizing structs
typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//*A*bstract *S*yntax *T*ree structs
//Do we need &&
typedef enum e_node_type
{
	N_PIPE,
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
}	t_node ;

typedef enum e_err_no
{
	ENO_SUCCESS = 0,
	ENO_GENERAL = 1,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND = 127,
	ENO_EXEC_255 = 255
}	t_err_no ;

typedef struct s_envls
{
	char			*key;
	char			*value;
	struct s_envls	*next;
}					t_envls;


//general struct
typedef struct s_data
{
	char	*cmd_line;
	t_token	*token_list;
	t_node	*ast;
	t_envls	*env;
	char	**envp;
	int		stdin;
	int		stdout;
	bool	heredoc_siginit;
	struct 	termios	original_terminal;
}	t_data;


//builtin

int		ft_exec_builtin(char **command, t_data *data);
int		ft_env(t_data *data);
int		ft_pwd(void);
int		ft_echo(char **command);
int		ft_unset(char **args, t_data *data);
int		ft_cd(char *dir_name, t_data *data);
int		ft_export(char **command, t_data *data);
int		check_key_format(char *str);

//envp
void	make_env_list(t_data *data);
char	*copy_key(char *str);
char	*copy_value(char *str);
void	update_val(t_data *min, char *key, char *value, bool make);

//cleanup
void	*free_or_add_list(void *ptr, bool clean);

void		print_env_list(t_token *head);



void		print_env_list(t_token *head);

/*PARSING*/

//parser_cleaner
void		clear_ast(t_node **ast, t_token *token_list);
void		clear_ast_nodes(t_node **left, t_node **right, t_token *token_list);
void		clear_cmd_node(t_node *node);
void		clear_io_list(t_io_node **lst);
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

//signal handling
void	sigquit_handler(int num);

//execution
void	init_tree(t_node *node, t_data *data);

#endif
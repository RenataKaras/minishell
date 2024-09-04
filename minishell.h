/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 17:52:07 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/04 18:37:37 by rshaheen      ########   odam.nl         */
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
typedef enum e_err_no
{
	ENO_SUCCESS = 0,
	ENO_GENERAL = 1,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND = 127,
	ENO_EXEC_255 = 255
}	t_err_no;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char			**env;
	int				stdin;
	int				stdout;
	t_env			*env_link_list;
	struct termios	original_term;

}	t_minishell;

extern t_minishell	g_minishell;


//builtin

int		ft_exec_builtin(char **command);
int		ft_env(void);
int		ft_pwd(void);
int		ft_echo(char **command);
int		ft_unset(char **args);
int		ft_cd(char *path);

//env
void	make_env_list(void);
char	*copy_key(char *str);
void	set_val_make_node(char *key, char *value, bool create);

//cleanup
void	*free_or_add_list(void *ptr, bool clean);


#endif
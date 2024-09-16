/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 17:52:07 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/16 14:50:18 by rshaheen      ########   odam.nl         */
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

typedef struct s_envls
{
	char			*key;
	char			*value;
	struct s_envls	*next;
}	t_envls;

typedef struct s_data
{
	char			**envp;
	int				stdin;
	int				stdout;
	t_envls			*env_link_list;
	struct termios	original_terminal;

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


#endif
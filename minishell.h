/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/18 17:52:07 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/03 17:45:33 by rshaheen      ########   odam.nl         */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char	**env;
	int		stdin;
	int		stdout;
	t_env	*env_link_list;

}	t_minishell;

extern t_minishell	g_minishell;


//builtin

int		ft_exec_builtin(char **command);
int		ft_env(void);
int		ft_pwd(void);
int		ft_echo(char **command);

//env
void	make_env_list(void);
void	update_or_create_node(char *key, char *value, bool create);

//cleanup
void	*free_or_add_list(void *ptr, bool clean);


#endif
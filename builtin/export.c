/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/09 13:59:24 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/10/03 14:50:52 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
* export command without any arguments in Bash, lists all the envp variables 
* marked for export. Each variable is printed in the format 
* declare -x key="value" if it has a value, 
* or declare -x key if it does not. the key "_" is usually 
* not included in the list of exported variables, so we dont print it at all
* outer while iterates through the list variables
* inner while loop iterates through the value chars to find $ or "
* In bash, export EXAMPLE_VAR1="Value with $ and "quotes""
* export will output 
* declare -x EXAMPLE_VAR1="Value with \$ and quotes"
* it skips the double quote and adds a backslash before $
* test here
*/
static void	print_export_list(t_data *data)
{
	t_envls	*list;
	size_t	i;

	list = data->env;
	while (list)
	{
		if (list->value != NULL && (ft_strcmp(list->key, "_") != 0))
		{
			printf("declare -x %s=\"", list->key);
			i = 0;
			while ((list->value)[i])
			{
				if ((list->value)[i] == '$' || (list->value)[i] == '"')
					printf("\\%c", list->value[i++]);
				else
					printf("%c", (list->value)[i++]);
			}
			printf("\"\n");
		}
		else if (list->value == NULL && (ft_strcmp(list->key, "_") != 0))
			printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

static int	export_err_msg(char *identifier)
{
	ft_putstr_fd("minishell: export `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("':not a valid identifier\n", 2);
	return (1);
}

bool	is_key_in_env_list(char *key, t_data *minishell)
{
	t_envls	*env_list;

	env_list = minishell->env;
	while (env_list)
	{
		if (ft_strcmp(key, env_list->key) == 0)
			return (true);
		env_list = env_list->next;
	}
	return (false);
}

int	ft_export(char **command, t_data *minishell)
{
	int		i;
	int		exit_status;
	char	*key;

	exit_status = 0;
	i = 1;
	if (!command[i])
		return (print_export_list(minishell), 0);
	while (command[i])
	{
		if (check_key_format(command[i]) == 0)
			exit_status = export_err_msg(command[i]);
		else
		{
			key = copy_key(command[i]);
			if (is_key_in_env_list(key, minishell) == true)
				update_val(minishell, key, copy_value(command[i]), false);
			else
				update_val(minishell, key, copy_value(command[i]), true);
		}
		i++;
	}
	return (exit_status);
}

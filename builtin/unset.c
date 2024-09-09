/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/04 14:34:46 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/09/09 15:34:20 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Validation rules:
 * 1. key starts with an alphabetical char (a-z, A-Z) or an underscore (_).
 * 2. After the first char, the rest of the key can consist of
 * alphanumeric characters(a-z, A-Z, 0-9) or underscores (_).
 * 3. The key may optionally include an equal sign ('=') 
 * 	which is used to separate the key
 *  from its value, but it should not be part of the key itself.
 *
 * Steps:
 * 1. Check if the 1st char is either an alphabetical character
 *    or an underscore. If not, return 0 indicating an invalid key.
 * 2. Start checking from the second char till an '=' or the end.
 * 3. If no alphanumeric nor an underscore found, return 0 (false).
 * 4. If all chars conform to the rules, return 1 (true) indicating a valid key.
*/
int	check_key_format(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	unset_helper(char *key)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = g_minishell.env_link_list;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
		{
			if (prev)
				prev->next = current->next;
			else
				g_minishell.env_link_list = current->next;
			free (current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}


int	ft_unset(char **args)
{
	int		i;
	bool	error;

	i = 1;
	if (!args[1])
		return (0);
	error = false;
	while (args[i])
	{
		if (!check_key_format(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("':not a valid identifier\n", 2);
			error = true;
		}
		else
			unset_helper(free_or_add_list(copy_key(args[i]), false));
		i++;
	}
	return (error);
}
//unset does not write any message in bash if variable not found
//unset is removing but does not remember what it removed later

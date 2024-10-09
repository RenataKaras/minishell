/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 17:44:31 by rkaras        #+#    #+#                 */
/*   Updated: 2024/10/09 18:10:09 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_dollar(t_data *data, int *i, char *str)
{
	int		start;
	char	*var;
	char	*env_val;

	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
		return ((*i)++, ft_strdup(""));
	else if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(data->exit_status));
	}
	else if (is_valid_var_char(str[*i]) == false)
		return (ft_strdup("$"));
	start = *i;
	while (is_valid_var_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	env_val = get_envlst_val(var, data->env);
	if (!env_val)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(env_val));
}

char	*cmd_pre_expander(t_data *data, char *str)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			result = strjoin_free(result, handle_squotes(str, &i));
		else if (str[i] == '"')
			result = strjoin_free(result, handle_dquotes(data, &i, str));
		else if (str[i] == '$')
			result = strjoin_free(result, handle_dollar(data, &i, str));
		else
			result = strjoin_free(result, handle_normal_str(str, &i));
	}
	return (result);
}

char	**expand(t_data *data, char *str)
{
	char	**expanded;
	int		i;

	str = cmd_pre_expander(data, str);
	if (!str)
		return (NULL);
	str = clean_empty_strs(str);
	if (!str)
		return (NULL);
	expanded = expander_split(str);
	free(str);
	if (!expanded)
		return (NULL);
	i = 0;
	while (expanded[i])
	{
		expanded[i] = strip_quotes(expanded[i]);
		i++;
	}
	return (expanded);
}

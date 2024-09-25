/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkaras <rkaras@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 17:44:31 by rkaras        #+#    #+#                 */
/*   Updated: 2024/09/25 16:35:02 by rkaras        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_dollar(t_data *data, int *i)
{
	int		start;
	char	*str;
	char	*var;
	char	*env_val;

	str = data->ast->args;
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

char	*cmd_pre_expander(t_data *data)
{
	char	*result;
	int		i;
	char	*str;

	str = data->ast->args;
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			result = strjoin_free(result, handle_squotes(str, &i));
		else if (str[i] == '"')
			result = strjoin_free(result, handle_dquotes(data, &i));
		else if (str[i] == '$')
			result = strjoin_free(result, handle_dollar(data, &i));
		else
			result = strjoin_free(result, handle_normal_str(str, &i));
	}
	return (result);
}

char	**expand(t_data *data)
{
	char	**expanded;
	char	*str;

	str = cmd_pre_expander(data);
	if (!str)
		return (NULL);
	str = clean_empty_strs(str);
	if (!str)
		return (NULL);
	expanded = expander_split(str);
	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_parser_util.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 15:21:28 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/08/21 17:21:00 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	remove_initial_space(const char *s, int start)
{
	while (s[start] == ' ')
		start++;
	return (start);
}
int	check_len(const char *s, int start, size_t len)
{
	// Check if the total length of the string `s` is less than or equal to `len`
	if (ft_strlen(s) <= len)
		return (ft_strlen(s) - start);// Return the length of the string from `start` to the end.
	if (ft_strlen(s) == 1 || start >= (int)ft_strlen(s))//if str is 1 char  or start is at NULL
		return (0);//
	else if (ft_strlen(s) - start < len)
		return (ft_strlen(s) - start);
	//If start is in the middle of the string and the remaining part is shorter than len, the function will:
//Return the length of the remaining part (ft_strlen(s) - start), which is the actual number of characters available from start to the end of the string.
	return (len);//if none of the above are met, return len
}
bool valid_substring(const char *s, int start, bool has_double_quote)
{
	if (s[start] == ' ' && s[start + 1] == '\0')
		return (true);
	else if ((s[start] == ' ' && has_double_quote == false)
		&& (s[start + 1] == '>'|| s[start + 1] == '<'
			|| s[start + 1] == '|'))
		return (true);
	else if (s[start] == ' ' && is_operator_or_null(s[start - 1]) == 1
			&& ft_isalpha(s[start + 1]) == 1 && has_double_quote == false)
		return (true);
	return (false);
}
char	*get_cmd(char *s, int unsigned start, size_t len)
{
	char	*substring;
	size_t	i;
	bool	has_double_quotes;

	i = 0;
	if (!s)
		return (NULL);
	start = remove_initial_space(s, start);
	len = check_len(s, start, len);
	//printf("print length after check%zu", len);
	substring = ft_calloc(len + 1, sizeof(char));
	if (substring == NULL)
		return (NULL);
	has_double_quotes = false;
	while (i < len && start < ft_strlen(s))
	{
		if (s[start] == '"')
			has_double_quotes = !has_double_quotes;
		if (valid_substring(s, start, has_double_quotes) == true)
			return (substring);
		substring = &s[start];
		i++;
		start++;
	}
	return (substring);
}

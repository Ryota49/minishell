/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 09:39:54 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/23 13:43:54 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_expandable(char c)
{
	if (c == '_' || c == '?'
		|| (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	is_char_var(char c)
{
	if (c == '_'
		|| (c >= '0' && c <= '9')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

char	*get_var(char *str, int *i)
{
	char	*var_name;
	char	*var;
	int		i_name;

	i_name = 0;
	var_name = malloc(sizeof(char) * 1);
	if (!var_name)
		return (NULL);
	var_name[0] = '\0';
	while (is_char_var(str[*i]))
	{
		var_name = add_char(var_name, str[*i]);
		if (!var_name)
			return (NULL);
		*i += 1;
		i_name++;
	}
	var_name[i_name] = '\0';
	var = getenv(var_name);
	if (!var)
		var = "";
	free(var_name);
	return (var);
}

// char	*remove_quotes(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	*new_str;

// 	new_str = malloc(sizeof(char) * strlen(str) - 2 + 1);
// 	if (!new_str)
// 		return (NULL);
// 	i = 1;
// 	j = 0;
// 	while (str[i + 1])
// 	{
// 		new_str[j] = str[i];
// 		i++;
// 		j++;
// 	}
// 	new_str[j] = '\0';
// 	free(str);
// 	return (new_str);
// }
char *remove_quotes(char *str)
{
	char *res;
	int i = 0;
	int j = 0;
	char quote = 0;

	res = malloc(strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	free(str);
	return res;
}

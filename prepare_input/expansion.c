/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:40:40 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/23 13:54:22 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	var_case(char *str, char **new_str, int	*i)
{
	char	*var;
	int		i_var;

	i_var = 0;
	var = get_var(str, *(&i));
	if (!var)
		*new_str = NULL;
	while (var && var[i_var])
	{
		*new_str = add_char(*new_str, var[i_var]);
		if (!*new_str)
			return ;
		i_var++;
	}
}

static void	do_expansion(char **str, char **new_str, int *i, t_minish minish)
{
	char	*value;
	char	*tmp;

	*i += 1;
	if ((*str)[*i] == '?')
	{
		value = ft_itoa(minish.g_exit_status);
		tmp = ft_strjoin(*new_str, value);
		free(*new_str);
		*new_str = tmp;
		free(value);
		*i += 1;
	}
	else
		var_case(*str, *(&new_str), *(&i));
	if (!*str || !*new_str)
	{
		*new_str = NULL;
		*str = NULL;
	}
}

static int	in_or_out_simple_quote(char c, int flag_quote)
{
	if (c == '\'' && flag_quote == 0)
		return (1);
	else if (c == '\'' && flag_quote == 1)
		return (0);
	return (flag_quote);
}

static char	*create_new_arg(char *str, t_minish minish)
{
	int		i;
	int		flag_quote;
	char	*new_str;

	i = 0;
	flag_quote = 0;
	new_str = malloc(sizeof(char) * 1);
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	while (str[i])
	{
		flag_quote = in_or_out_simple_quote(str[i], flag_quote);
		if (str[i] == '$' && is_expandable(str[i + 1]) && !flag_quote)
			do_expansion(&str, &new_str, &i, minish);
		else
		{
			new_str = add_char(new_str, str[i]);
			if (!new_str)
				return (NULL);
			i++;
		}
	}
	free(str);
	return (new_str);
}

t_cmd	*expansion(t_minish minish, t_cmd *cmds)
{
	t_cmd	*p_cmds;
	int		i;

	p_cmds = cmds;
	while (p_cmds)
	{
		i = 0;
		while (p_cmds->argv[i])
		{
			if (p_cmds->argv[i][0] != '\'')
				p_cmds->argv[i] = create_new_arg(p_cmds->argv[i], minish);
			p_cmds->argv[i] = remove_quotes(p_cmds->argv[i]);
			i++;
		}
		p_cmds = p_cmds->next;
	}
	return (cmds);
}

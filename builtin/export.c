/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:14 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/25 08:51:12 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_key(char *str)
{
	char	*key;
	int		len;

	len = 0;
	while (str[len] && str[len + 1] != '=')
		len++;
	key = ft_strndup(str, 0, len);
	return (key);
}

static int	verif_export(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '_'
		|| (str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] >= 'a' && str[i] <= 'z'))
	{
		while (str[i] == '_' || isalnum(str[i]))
		{
			if (str[i + 1] == '\0' 
				|| (str[i + 1] == '=' && str[i + 2]))
				return (1);
			i++;
		}
		return (0);
	}
	return (0);
}

static int	export_no_args(t_minish *minish)
{
	int	i;

	i = 0;
	while (minish->envp[i])
	{
		printf("declare -x %s\n", minish->envp[i]);
		i++;
	}
	return (0);
}

static int	export_invalid_id(char *argv)
{
	(void)argv;
	write(2, "export: ", 8);
	write(2, "not a valid identifier\n", 23);
	return (1);	
}

int	builtin_export(t_minish *minish, char **argv)
{
	char	*key;
	int		i;
	int		res;

	i = 1;
	res = 0;
	if (!argv[i])
		res = export_no_args(minish);
	while (argv[i])
	{
		if (!verif_export(argv[i]))
		{
			res = export_invalid_id(argv[i++]);
			continue ;
		}
		key = get_key(argv[i]);
		if (!key)
			return (1);
		if (!change_value(minish->envp, key, argv[i]))
			minish->envp = add_var(minish->envp, argv[i]);
		free(key);
		i++;
	}
	return (res);
}

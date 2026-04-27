/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 09:35:18 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/26 09:42:40 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_value(char **envp, char *str)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0
			&& envp[i][ft_strlen(str)] == '=')
		{
			start = ft_strlen(str) + 1;
			end = ft_strlen(envp[i]);
			return (ft_strndup(envp[i], start, end));
		}
		i++;
	}
	return (NULL);
}

static int	copy_str_tab(char **tab, char **new_tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
		{
			clean_str_tab(new_tab, i);
			return (-1);
		}
		i++;
	}
	return (i);
}

char	**add_var(t_env *env, char **tab, char *str)
{
	char	**new_tab;
	int		new_len;
	int		i;

	new_len = tab_str_len(tab) + 2;
	new_tab = malloc(sizeof(char *) * new_len);
	if (!new_tab)
		return (NULL);
	i = copy_str_tab(tab, new_tab);
	if (i == -1)
		return (NULL);
	new_tab[i] = ft_strdup(str);
	if (!new_tab[i])
	{
		clean_str_tab(new_tab, i);
		return (NULL);
	}
	new_tab[i + 1] = NULL;
	env->exported = add_value_tab_int(env->exported, 1, new_len - 2);
	if (is_value_empty(new_tab[i]))
		env->has_value = add_value_tab_int(env->has_value, 0, new_len - 2);
	else
		env->has_value = add_value_tab_int(env->has_value, 1, new_len - 2);
	free_str_tab(tab);
	return (new_tab);
}

int	change_value(t_env *env, char *key, char *str)
{
	int		i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], key, ft_strlen(key)) == 0
			&& (env->envp[i][ft_strlen(key)] == '='
			|| env->envp[i][ft_strlen(key)] == '\0'))
		{
			free(env->envp[i]);
			env->envp[i] = ft_strdup(str);
			if (is_value_empty(str))
				env->has_value[i] = 0;
			else
				env->has_value[i] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_export(char *str)
{
	int	i;

	i = 0;
	printf("declare -x ");
	while (str[i] && str[i] != '=')
	{
		printf("%c", str[i]);
		i++;
	}
	printf("=\"");
	i++;
	while (str[i])
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\"\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 09:35:18 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/25 08:47:30 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_value(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0
			&& envp[i][ft_strlen(str)] == '=')
			return (envp[i] + ft_strlen(str) + 1);
		i++;
	}
	return (NULL);
}

static int	copy_tab(char **tab, char **new_tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
		{
			clean_tab(new_tab, i);
			return (-1);
		}
		i++;
	}
	return (i);
}

char	**add_var(char **tab, char *str)
{
	char	**new_tab;
	int		i;

	new_tab = malloc(sizeof(char *) * (tab_len(tab) + 2));
	if (!new_tab)
		return (NULL);
	i = copy_tab(tab, new_tab);
	if (i == -1)
		return (NULL);
	new_tab[i] = ft_strdup(str);
	if (!new_tab[i])
	{
		clean_tab(new_tab, i);
		return (NULL);
	}
	new_tab[i + 1] = NULL;
	free_tab(tab);
	return (new_tab);
}

int	change_value(char **envp, char *key, char *str)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
			&& (envp[i][ft_strlen(key)] == '='
				|| envp[i][ft_strlen(key)] == '\0'))
		{
			free(envp[i]);
			envp[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:21 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/17 14:35:11 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	copy_tab_less_i(char **tab, char **new_tab, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[j])
	{
		if (j == index)
		{
			j++;
			continue ;
		}
		new_tab[i] = ft_strdup(tab[j]);
		if (!new_tab[i])
			clean_tab(new_tab, i);
		i++;
		j++;
	}
	new_tab[i] = NULL;
}

static char	**dup_tab_less_i(char **tab, int index)
{
	char	**new_tab;

	new_tab = malloc(sizeof(char *) * tab_len(tab));
	if (!new_tab)
		return (NULL);
	copy_tab_less_i(tab, new_tab, index);
	free_tab(tab);
	return (new_tab);
}

static int	get_index(char **tab, char *key)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], key, ft_strlen(key)) == 0
			&& tab[i][ft_strlen(key)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	builtin_unset(t_minish *minish, char **argv)
{
	int		i;

	if (!argv[1])
		return (0);
	i = get_index(minish->envp, argv[1]);
	if (i == -1)
		return (0);
	minish->envp = dup_tab_less_i(minish->envp, i);
	return (0);
}

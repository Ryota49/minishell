/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 09:39:32 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/28 11:49:43 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	*add_value_tab_int(int *tab, int value, int len_tab)
{
	int	*new;
	int	i;

	new = malloc(sizeof(int) * (len_tab + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len_tab)
	{
		new[i] = tab[i];
		i++;
	}
	new[i] = value;
	free(tab);
	return (new);
}

int	tab_str_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**dup_str_tab(char **tab)
{
	char	**new_tab;
	int		i;

	new_tab = malloc(sizeof(char *) * (tab_str_len(tab) + 1));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
		{
			clean_str_tab(tab, i);
			return (NULL);
		}
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

void	clean_str_tab(char **tab, int i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

int	*dup_tab_int_less_i(int *tab, int index, int old_len)
{
	int	*new_tab;
	int	i;
	int	j;
	int	new_len;

	new_len = old_len - 1;
	new_tab = malloc(sizeof(int) * new_len);
	if (!new_tab)
		return (NULL);
	i = 0;
	j = 0;
	while (i < new_len)
	{
		if (j == index)
		{
			j++;
			continue ;
		}
		new_tab[i] = tab[j];
		i++;
		j++;
	}
	free(tab);
	return (new_tab);
}

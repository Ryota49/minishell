/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:59:50 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/29 10:05:39 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cmp_export_name(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '=' && s2[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if ((s1[i] == '=' || s1[i] == '\0') && (s2[i] == '=' || s2[i] == '\0'))
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	*build_index_tab(int len)
{
	int	*idx;
	int	i;

	idx = malloc(sizeof(int) * len);
	if (!idx)
		return (NULL);
	i = 0;
	while (i < len)
	{
		idx[i] = i;
		i++;
	}
	return (idx);
}

static void	sort_export_index(t_minish *minish, int *idx, int len)
{
	int	i;
	int	tmp;

	i = 0;
	while (i < len - 1)
	{
		if (cmp_export_name(minish->env->envp[idx[i]],
				minish->env->envp[idx[i + 1]]) > 0)
		{
			tmp = idx[i];
			idx[i] = idx[i + 1];
			idx[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

static void	print_sorted_export(t_minish *minish, int *idx, int len)
{
	int	i;
	int	real;

	i = 0;
	while (i < len)
	{
		real = idx[i];
		if (minish->env->exported[real])
		{
			if (!minish->env->has_value[real])
				printf("declare -x %s\n", minish->env->envp[real]);
			else
				print_export(minish->env->envp[real]);
		}
		i++;
	}
}

int	export_no_args(t_minish *minish)
{
	int	len;
	int	*idx;

	len = tab_str_len(minish->env->envp);
	idx = build_index_tab(len);
	if (!idx)
		return (1);
	sort_export_index(minish, idx, len);
	print_sorted_export(minish, idx, len);
	free(idx);
	return (0);
}

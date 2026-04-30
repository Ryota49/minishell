/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 09:02:06 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/29 09:33:31 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_value_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

static void	fill_int_tab(int *tab, int tab_len, int value)
{
	int	i;

	i = 0;
	while (i < tab_len)
	{
		tab[i] = value;
		i++;
	}
}

t_env	*init_env_no_base(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->envp = calloc(sizeof(char *), 2);
	env->exported = calloc(sizeof(int), 1);
	env->has_value = calloc(sizeof(int), 1);
	if (!env->envp || !env->exported || !env->has_value)
		return (NULL);
	env->envp[1] = NULL;
	fill_int_tab(env->exported, 1, 0);
	fill_int_tab(env->has_value, 1, 0);
	return (env);
}

t_env	*init_envp(char **tab)
{
	t_env	*env;

	if (!tab)
	{
		env = init_env_no_base();
		return (env);
	}
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->envp = dup_str_tab(tab);
	env->exported = malloc(sizeof(int) * tab_str_len(tab));
	env->has_value = malloc(sizeof(int) * tab_str_len(tab));
	if (!env->envp || !env->exported || !env->has_value)
		return (NULL);
	fill_int_tab(env->exported, tab_str_len(tab), 1);
	fill_int_tab(env->has_value, tab_str_len(tab), 1);
	return (env);
}

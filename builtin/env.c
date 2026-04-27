/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:32 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/24 09:57:46 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_env(t_env *env, char **argv)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return (127);
	}
	while (env->envp[i])
	{
		if (env->exported[i] == 1 && env->has_value[i] == 1)
			printf("%s\n", env->envp[i]);
		i++;
	}
	return (0);
}

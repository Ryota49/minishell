/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:32 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/17 13:25:43 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_env(char **envp, char **argv)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		printf("env: '%s': No such file or directory\n", argv[1]);
		return (127);
	}
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

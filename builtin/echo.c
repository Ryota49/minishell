/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:21:31 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/14 11:49:44 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_echo(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argv[i] && ft_strcmp(argv[i], "-n"))
	{
		flag = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}

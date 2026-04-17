/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 02:10:23 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/22 12:44:16 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_non_empty(char **argv)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			result++;
		i++;
	}
	return (result);
}

void	remove_empty_argv(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**new;

	if (!cmd || !cmd->argv)
		return ;
	new = malloc(sizeof(char *) * (count_non_empty(cmd->argv) + 1));
	if (!new)
		return ;
	i = 0;
	j = 0;
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] != '\0')
		{
			new[j] = cmd->argv[i];
			j++;
		}
		i++;
	}
	new[j] = NULL;
	free(cmd->argv);
	cmd->argv = new;
}

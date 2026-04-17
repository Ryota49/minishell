/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:53:18 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/14 17:32:06 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

int	**create_pipes(int nb_pipes)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * nb_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
		{
			perror("pipe");
			close_all_pipes(pipes, i);
			free_pipes(pipes, i);
			free (pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	close_all_pipes(int **pipes, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	free_pipes(int **pipes, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

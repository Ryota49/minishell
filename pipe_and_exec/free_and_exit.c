/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 02:10:23 by jemonthi          #+#    #+#             */
/*   Updated: 2026/04/24 09:54:19 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_not_found_exit(t_minish *minish, t_exec *exec)
{
	ft_putstr_fd("minishell: command not found\n", 2);
	free_child_pipes(exec);
	free_all(minish, 1);
	_exit(127);
}

void	free_child_pipes(t_exec *exec)
{
	if (exec->nb_cmds > 1)
	{
		close_all_pipes(exec->pipes, exec->nb_cmds - 1);
		free_pipes(exec->pipes, exec->nb_cmds - 1);
	}
}

void	free_minish_exit_zero(t_minish *minish, t_exec *exec)
{
	if (exec->nb_cmds > 1)
	{
		close_all_pipes(exec->pipes, exec->nb_cmds - 1);
		free_pipes(exec->pipes, exec->nb_cmds - 1);
	}
	free_all(minish, 1);
	_exit(0);
}

void	free_minish_exit_one(t_minish *minish, t_exec *exec)
{
	if (exec->nb_cmds > 1)
	{
		close_all_pipes(exec->pipes, exec->nb_cmds - 1);
		free_pipes(exec->pipes, exec->nb_cmds - 1);
	}
	free_all(minish, 1);
	_exit(1);
}

void	call_free_all(char *path, t_minish *minish, t_exec *exec)
{
	if (exec->nb_cmds > 1)
	{
		close_all_pipes(exec->pipes, exec->nb_cmds - 1);
		free_pipes(exec->pipes, exec->nb_cmds - 1);
	}
	free(path);
	free_all(minish, 1);
}

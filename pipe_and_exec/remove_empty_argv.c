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

void	prepare_single_pid(t_minish *minish, t_exec *exec)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	if (minish->cmds->redirs)
	{
		if (apply_redirs(minish->cmds->redirs))
		{
			free_all(minish, 1);
			_exit(1);
		}
	}
	exec_external(minish, exec);
	free_all(minish, 1);
	_exit(1);
}

int	count_non_empty(char **argv)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (argv[0][0] == '\0')
		i++;
	while (argv[i])
	{
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
		if (cmd->argv[i][0] == '\0' && i == 0)
		{
			free(cmd->argv[i]);
			i++;
		}
		new[j] = cmd->argv[i];
		j++;
		i++;
	}
	new[j] = NULL;
	free(cmd->argv);
	cmd->argv = new;
}

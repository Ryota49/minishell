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

void	close_fd_saved(int saved_stdout, int saved_stdin)
{
	close(saved_stdout);
	close(saved_stdin);
}

// Return 1 if it's a builtin //
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0);
}

/* save last stdin/stdout with dup then call exec 
	(usefull for appended ( > or >> or < character)) */

void	exec_single_builtin(t_minish *minish)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (minish->cmds->redirs)
	{
		if (apply_redirs(minish->cmds->redirs))
		{
			minish->exit_status = 1;
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return ;
		}
	}
	if (ft_strncmp(minish->cmds->argv[0], "exit", 5) == 0)
		close_fd_saved(saved_stdout, saved_stdin);
	minish->exit_status = exec_builtin(minish->cmds, minish, 0);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

// We look for the right function to call //
int	exec_builtin(t_cmd *cmd, t_minish *minish, int is_child)
{
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (builtin_cd(cmd->argv, minish->env));
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (builtin_export(minish, cmd->argv));
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (builtin_unset(minish, cmd->argv));
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (builtin_env(minish->env, cmd->argv));
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (builtin_exit(minish, cmd->argv, is_child));
	return (0);
}

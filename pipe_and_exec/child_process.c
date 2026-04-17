/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 04:11:02 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/15 04:58:38 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipes_child(int i, int nb_cmds, int **pipes)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < nb_cmds - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
}

void	check_ret_value(int ret, char *path, t_cmd *cmd, char **envp)
{
	if (ret == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("minishell: Permission denied\n", 2);
			exit (126);
		}
		else if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			exit (127);
		}
		else if (errno == ENOEXEC)
		{
			if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
				execve("/bin/sh", cmd->argv, envp);
			else
				execve("/bin/sh", (char *[]){"sh", path, NULL}, envp);
		}
	}
}

void	check_access(t_cmd *cmd)
{
	int	fd;

	if (access(cmd->argv[0], F_OK) == 0)
	{
		fd = open(cmd->argv[0], O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			ft_putstr_fd("minishell: Is a directory\n", 2);
			exit (126);
		}
	}
}

void	exec_external(t_cmd *cmd, char **envp)
{
	char	*path;
	int		ret;

	if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
	{
		check_access(cmd);
		ret = execve(cmd->argv[0], cmd->argv, envp);
	}
	else
	{
		path = resolve_cmd(cmd->argv[0], envp);
		if (!path)
		{
			ft_putstr_fd("minishell: command not found\n", 2);
			exit(127);
		}
		ret = execve(path, cmd->argv, envp);
	}
	check_ret_value(ret, path, cmd, envp);
	free(path);
	exit(1);
}

/* ---- Child process ---- */

void	child_process(t_minish *minish, t_cmd *cmd, int i, t_exec *exec)
{
	int	ret;

	signal(SIGPIPE, SIG_DFL);
	setup_pipes_child(i, exec->nb_cmds, exec->pipes);
	if (cmd->redirs)
	{
		if (apply_redirs(cmd->redirs))
			exit(1);
	}
	close_all_pipes(exec->pipes, exec->nb_cmds - 1);
	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		exit(0);
	if (is_builtin(cmd->argv[0]))
	{
		ret = exec_builtin(cmd, minish, 1);
		exit(ret);
	}
	exec_external(cmd, minish->envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 02:10:23 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/22 12:44:16 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ---- Single command execution (no pipe)---- */

static void	exec_single(t_minish *minish, t_exec *exec)
{
	pid_t	pid;
	int		status;

	if (is_builtin(minish->cmds->argv[0]))
	{
		exec_single_builtin(minish);
		return ;
	}
	pid = fork();
	if (pid == 0)
		prepare_single_pid(minish, exec);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		minish->exit_status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		minish->exit_status = WEXITSTATUS(status);
}

static void	waitpid_all(t_minish *minish, int nb_cmds, pid_t *pids)
{
	int		i;
	int		status;
	int		last_status;
	pid_t	last_pid;

	last_pid = pids[nb_cmds - 1];
	i = 0;
	last_status = 0;
	while (i < nb_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (pids[i] == last_pid)
			last_status = status;
		i++;
	}
	if (WIFSIGNALED(last_status))
	{
		if (WTERMSIG(last_status) == SIGINT)
			write(1, "\n", 1);
		minish->exit_status = 128 + WTERMSIG(last_status);
	}
	else if (WIFEXITED(last_status))
		minish->exit_status = WEXITSTATUS(last_status);
}

/* ---- Multi command execution (atleast 1 pipe)---- */

static int	fork_all(t_minish *minish, t_exec *exec, pid_t *pids)
{
	t_cmd	*cur;
	int		i;

	cur = minish->cmds;
	i = 0;
	while (cur)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork");
			return (-1);
		}
		if (pids[i] == 0)
			child_process(minish, cur, i, exec);
		cur = cur->next;
		i++;
	}
	return (0);
}

static void	exec_multi(t_minish *minish, t_exec *exec)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * exec->nb_cmds);
	if (!pids)
	{
		close_all_pipes(exec->pipes, exec->nb_cmds - 1);
		free_pipes(exec->pipes, exec->nb_cmds - 1);
		return ;
	}
	if (fork_all(minish, exec, pids) < 0)
	{
		close_all_pipes(exec->pipes, exec->nb_cmds - 1);
		free_pipes(exec->pipes, exec->nb_cmds - 1);
		free(pids);
		return ;
	}
	close_all_pipes(exec->pipes, exec->nb_cmds - 1);
	waitpid_all(minish, exec->nb_cmds, pids);
	free_pipes(exec->pipes, exec->nb_cmds - 1);
	free(pids);
}
/* ---- Main execute function ---- */

void	execute(t_minish *minish)
{
	t_exec	exec;
	t_cmd	*cur;

	cur = minish->cmds;
	signal(SIGPIPE, SIG_IGN);
	while (cur)
	{
		remove_empty_argv(cur);
		cur = cur->next;
	}
	prepare_heredoc(minish, minish->cmds);
	exec.nb_cmds = count_cmds(minish->cmds);
	if (exec.nb_cmds == 1)
	{
		if (!minish->cmds->argv || !minish->cmds->argv[0]
			|| (minish->cmds->argv[0][0] == '\0'
			&& minish->cmds->argv[1] == NULL))
			return ;
		exec_single(minish, &exec);
		return ;
	}
	exec.pipes = create_pipes(exec.nb_cmds - 1);
	if (!exec.pipes)
		return ;
	exec_multi(minish, &exec);
}

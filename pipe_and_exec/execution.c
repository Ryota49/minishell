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

static void	exec_single(t_minish *minish)
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
	{
		if (minish->cmds->redirs)
		{
			if (apply_redirs(minish->cmds->redirs))
				exit(1);
		}
		signal(SIGPIPE, SIG_DFL);
		exec_external(minish->cmds, minish->envp);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		minish->g_exit_status = WEXITSTATUS(status);
		g_exit_status = minish->g_exit_status;
	}
}
/* on waitpid tous les pids et on check le status ainsi que si on a eu un signal pour les pipes*/

static void waitpid_all(t_minish *minish, int nb_cmds, pid_t *pids)
{
	int i;
	int status;
	int signal;
	int	written;

	i = 0;
	written = 0;
	while (i < nb_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			signal = WTERMSIG(status);
			if (signal == SIGPIPE && !written)
			{
				ft_putstr_fd("minishell: Broken pipe\n", 2);
				written = 1;
			}
			minish->g_exit_status = 128 + signal;
		}
		else if (WIFEXITED(status))
			minish->g_exit_status = WEXITSTATUS(status);
		i++;
	}
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
		return ;
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

int	count_non_empty(char **argv)
{
	int	i;
	int	j;
	int	result;

	i = 0;
	j = 0;
	result = 0;
	while (argv[i])
	{
		if (argv[i][j] != '\0')
			result++;
		i++;
	}
	return (result);
}

void remove_empty_argv(t_cmd *cmd)
{
    int i;
    int j;
    char **new;

    if (!cmd || !cmd->argv)
        return;

    new = malloc(sizeof(char *) * (count_non_empty(cmd->argv) + 1));
    if (!new)
        return;
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

/* ---- Main execute function ---- */

void	execute(t_minish *minish)
{
	t_exec	exec;
	t_cmd *cur = minish->cmds;

	signal(SIGPIPE, SIG_IGN);
	while (cur)
	{
    	remove_empty_argv(cur);
    	cur = cur->next;
	}
	prepare_heredoc(minish->cmds);
	exec.nb_cmds = count_cmds(minish->cmds);
	if (exec.nb_cmds == 1)
	{
		if (!minish->cmds->argv || !minish->cmds->argv[0] || (minish->cmds->argv[0][0] == '\0' && minish->cmds->argv[1] == NULL))
			return ;
		exec_single(minish);
		return ;
	}
	exec.pipes = create_pipes(exec.nb_cmds - 1);
	if (!exec.pipes)
		return ;
	exec_multi(minish, &exec);
}

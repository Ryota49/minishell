/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 09:50:10 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/22 12:21:51 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	strcmp_heredoc(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (s1[i] - s2[i]);
}

static void	write_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp_heredoc(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

static void	handle_heredoc(t_redir *redir)
{
	int		fd;

	fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc");
		g_exit_status = 1;
		return ;
	}
	write_heredoc(fd, redir->filename);
	close(fd);
	free(redir->filename);
	redir->filename = ft_strdup("/tmp/minishell_heredoc");
}

void	prepare_heredoc(t_cmd *cmds)
{
	t_cmd	*cur;
	t_redir	*redir;

	cur = cmds;
	while (cur)
	{
		redir = cur->redirs;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
				handle_heredoc(redir);
			redir = redir->next;
		}
		cur = cur->next;
	}
}

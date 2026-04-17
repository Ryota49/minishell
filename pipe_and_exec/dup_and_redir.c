/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 02:38:53 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/15 04:51:22 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* some test had quotes still in filename so we remove them*/

char	*remove_quotes_filename(char *str)
{
	char	*res;
	int		i;
	int		j;
	char	quote;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				res[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

/* redir for stdin */

int	apply_redir_in(t_redir *redir)
{
	int	fd;
	char *filename = remove_quotes_filename(redir->filename);

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->filename);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

/* redir for stdout */

int	apply_redir_out(t_redir *redir)
{
	int	fd;
	int	flags;
	char *filename = remove_quotes_filename(redir->filename);

	if (redir->type == TOKEN_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror(redir->filename);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

/* Redirections depending on token */

int	apply_redirs(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == TOKEN_REDIR_IN)
		{
			if (apply_redir_in(redirs))
				return (1);
		}
		else if (redirs->type == TOKEN_REDIR_OUT
			|| redirs->type == TOKEN_APPEND)
		{
			if (apply_redir_out(redirs))
				return (1);
		}
		else if (redirs->type == TOKEN_HEREDOC)
		{
			if (apply_redir_in(redirs))
				return (1);
		}
		redirs = redirs->next;
	}
	return (0);
}

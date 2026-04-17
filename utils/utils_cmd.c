/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 08:41:23 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/21 14:25:59 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**cpy_tab_str(char **tab, int size)
{
	int		i;
	char	**cpy_tab;

	i = 0;
	cpy_tab = malloc(sizeof(char *) * (size + 2));
	if (tab)
	{
		while (tab[i])
		{
			cpy_tab[i] = tab[i];
			i++;
		}
	}
	return (cpy_tab);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->has_pipe = 0;
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg(t_cmd *cmd, char *value)
{
	char	**new_argv;
	int		i;

	if (!cmd || !value)
		return ;
	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[i])
			i++;
	}
	new_argv = cpy_tab_str(cmd->argv, i);
	if (!new_argv)
		return ;
	new_argv[i] = strdup(value);
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

void	add_redir(t_cmd *cmd, t_token_type type, char *filename)
{
	t_redir	*redir;
	t_redir	*tmp;

	if (!cmd || !filename)
		return ;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	redir->type = type;
	redir->filename = strdup(filename);
	redir->next = NULL;
	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return ;
	}
	tmp = cmd->redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
}

void	add_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

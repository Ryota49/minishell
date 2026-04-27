/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:11:42 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/26 09:42:19 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		tokens->next = NULL;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next_cmd;
	t_redir	*next_redir;

	while (cmds)
	{
		next_cmd = cmds->next;
		cmds->next = NULL;
		free_str_tab(cmds->argv);
		while (cmds->redirs)
		{
			next_redir = cmds->redirs->next;
			cmds->redirs->next = NULL;
			free(cmds->redirs->filename);
			free(cmds->redirs);
			cmds->redirs = next_redir;
		}
		free(cmds);
		cmds = next_cmd;
	}
}

void	free_all(t_minish *minish, int end)
{
	if (minish->input)
		free(minish->input);
	if (minish->tokens)
	{
		free_tokens(minish->tokens);
		minish->tokens = NULL;
	}
	if (minish->cmds)
	{
		free_cmds(minish->cmds);
		minish->cmds = NULL;
	}
	if (end && minish->env)
	{
		if (minish->env->exported)
			free(minish->env->exported);
		if (minish->env->has_value)
			free(minish->env->has_value);
		if (minish->env->envp)
			free_str_tab(minish->env->envp);
		free(minish->env);
	}
}

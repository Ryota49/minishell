/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 08:41:11 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/21 14:45:10 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd	*syntax_error(t_cmd *cmds)
{
	printf("minishell: syntax error\n");
	free_cmds(cmds);
	return (NULL);
}

static int	is_redir(t_token_type type)
{
	if (type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC
		|| type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_IN)
		return (1);
	return (0);
}

static int	verif_syntax(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (i == 0 && tokens->type != TOKEN_WORD)
			return (0);
		if (tokens->type == TOKEN_PIPE)
		{
			if (!tokens->next || tokens->next->type != TOKEN_WORD)
				return (0);
		}
		if (is_redir(tokens->type))
		{
			if (!tokens->next || tokens->next->type != TOKEN_WORD)
				return (0);
			tokens = tokens->next;
			i++;
		}
		i++;
		tokens = tokens->next;
	}
	return (i);
}

static t_token	*create_command(t_token *tokens, t_cmd *current)
{
	if (tokens->type == TOKEN_WORD)
		add_arg(current, tokens->value);
	else if (is_redir(tokens->type))
	{
		add_redir(current, tokens->type, tokens->next->value);
		tokens = tokens->next;
	}
	return (tokens->next);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = NULL;
	if (!verif_syntax(tokens))
		return (syntax_error(cmds));
	while (tokens)
	{
		current = new_cmd();
		if (!current)
			return (NULL);
		while (tokens && tokens->type != TOKEN_PIPE)
		{
			tokens = create_command(tokens, current);
		}
		add_cmd(&cmds, current);
		if (tokens && tokens->type == TOKEN_PIPE)
		{
			current->has_pipe = 1;
			tokens = tokens->next;
		}
	}
	return (cmds);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:14:29 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/21 14:23:40 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	tokenize_arrow(const char *input, size_t i, t_token **tokens)
{
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			add_token(&(*tokens), new_token(TOKEN_APPEND, ">>", 0));
			i++;
		}
		else
			add_token(&(*tokens), new_token(TOKEN_REDIR_OUT, ">", 0));
	}
	else
	{
		if (input[i + 1] == '<')
		{
			add_token(&(*tokens), new_token(TOKEN_HEREDOC, "<<", 0));
			i++;
		}
		else
			add_token(&(*tokens), new_token(TOKEN_REDIR_IN, "<", 0));
	}
	i++;
	return (i);
}

static int	tokenize_word(const char *input, size_t i, t_token **tokens)
{
	size_t	start;
	char	quote;

	start = i;
	quote = 0;
	while (input[i])
	{
		if (!quote && (isspace(input[i]) || input[i] == '|'
				|| input[i] == '<' || input[i] == '>'))
			break ;
		if (input[i] == '\'' || input[i] == '"')
		{
			if (!quote)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		i++;
	}
	add_token(&(*tokens),
		new_token(TOKEN_WORD, ft_strndup(input, start, i - 1), 1));
	return (i);
}

t_token	*tokenize(const char *input)
{
	t_token	*tokens;
	size_t	i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '|')
		{
			add_token(&tokens, new_token(TOKEN_PIPE, "|", 0));
			i++;
		}
		else if (input[i] == '>' || input[i] == '<')
			i = tokenize_arrow(input, i, &tokens);
		else
			i = tokenize_word(input, i, &tokens);
	}
	return (tokens);
}

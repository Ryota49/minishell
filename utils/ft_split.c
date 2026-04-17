/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:52:37 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/10 13:36:15 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_words(char const *s, char sep)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (s[i] != sep && s[i] != '\0')
		count++;
	while (s[i])
	{
		if (s[i] == sep && s[i + 1] != sep && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	*worddup(char const *src, char c)
{
	int		i;
	int		len;
	char	*dest;

	len = 0;
	while (src[len] && src[len] != c)
		len++;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	fill_tab(char **new, char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] != c) && (i == 0 || s[i - 1] == c))
		{
			new[j] = worddup(&s[i], c);
			if (!new[j])
			{
				free_tab(new);
				return (0);
			}
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**new;

	if (!s)
		return (NULL);
	new = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!new)
		return (NULL);
	if (!fill_tab(new, s, c))
		return (NULL);
	return (new);
}

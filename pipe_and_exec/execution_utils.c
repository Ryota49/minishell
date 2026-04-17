/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:53:18 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/14 17:32:06 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*call_join_s3(char *res, char *s3, size_t i)
{
	size_t	j;

	j = 0;
	while (s3[j])
	{
		res[i] = s3[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
	{
		res[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res = call_join_s3(res, s3, i);
	return (res);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

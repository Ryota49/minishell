/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 07:56:57 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/19 07:57:11 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	verif_max_long(char *s, int i)
{
	int				j;
	unsigned int	len_limit;
	char			*long_max;

	j = 0;
	len_limit = 19;
	long_max = "9223372036854775807";
	if (i != 0)
		len_limit++;
	if (ft_strlen(s) > len_limit)
		return (0);
	if (ft_strlen(s) < len_limit)
		return (1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (s[i] > long_max[j])
			return (0);
		j++;
		i++;
	}
	return (1);
}

static int	verif_min_long(char *s, int i)
{
	char	*long_min;

	long_min = "-9223372036854775808";
	if (ft_strlen(s) > 20)
		return (0);
	if (ft_strlen(s) < 20)
		return (1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (s[i] > long_min[i])
			return (0);
		i++;
	}
	return (1);
}

int	verif_long(char *s)
{
	int		i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			return (verif_min_long(s, i));
	return (verif_max_long(s, i));
}

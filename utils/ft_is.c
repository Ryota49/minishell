/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 07:59:20 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/29 09:33:37 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isalpha(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int x)
{
	if (x >= '0' && x <= '9')
		return (1);
	else
		return (0);
}

int	ft_isalnum(int x)
{
	if (ft_isdigit(x) || ft_isalpha(x))
		return (8);
	else
		return (0);
}

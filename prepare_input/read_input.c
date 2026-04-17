/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:13:12 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/23 13:25:19 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	verif_quotes(const char *str)
{
	int	i;
	int flag_in_one;
	int flag_in_two;

	flag_in_one = 0;
	flag_in_two = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && flag_in_one)
			flag_in_one = 0;
		else if (str[i] == '\'' && !flag_in_one && !flag_in_two)
			flag_in_one = 1;
		else if (str[i] == '\"' && flag_in_two)
			flag_in_two = 0;
		else if (str[i] == '\"' && !flag_in_two && !flag_in_one)
			flag_in_two = 1;
		i++;
	}
	if (flag_in_one || flag_in_two)
	{
		printf("Error: Invalid use of quotes\n");
		return (0);
	}
	return (1);
}

static int	is_empty(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*read_input(void)
{
	char	*input;
	int		i;

	i = 0;
	while (i < 1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (is_empty(input) || !verif_quotes(input))
		{
			free(input);
			continue ;
		}
		i++;
	}
	return (input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:43 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/14 11:31:16 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exit_too_many_arg(void)
{
	write(2, "exit: too many arguments\n", 25);
	return (1);
}

static int	exit_numeric_error(char *arg)
{
	write(2, "exit: ", 6);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
	exit(2);
}

static int	is_code_exit(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	exit_not_child(t_minish *minish, char **argv)
{
	long	arg;
	char	*arg_cpy;

	if (argv[2])
		return (exit_too_many_arg());
	if (!argv[1])
	{
		free_all(minish);
		free_tab(minish->envp);
		exit(minish->g_exit_status);
	}
	if (!is_code_exit(argv[1]) || !verif_max_long(argv[1]))
	{
		arg_cpy = argv[1];
		free_all(minish);
		free_tab(minish->envp);
		exit_numeric_error(arg_cpy);
	}
	arg = ft_atol(argv[1]);
	free_all(minish);
	free_tab(minish->envp);
	exit((unsigned char)arg);
}

int	builtin_exit(t_minish *minish, char **argv, int is_child)
{
	long	arg;

	if (!is_child)
		return (exit_not_child(minish, argv));
	else
	{
		if (!argv[1])
			exit(minish->g_exit_status);
		if (!is_code_exit(argv[1]) || !verif_max_long(argv[1]))
			exit_numeric_error(argv[1]);
		if (argv[2])
			return (1);
		arg = ft_atol(argv[1]);
		exit((unsigned char)arg);
	}
}

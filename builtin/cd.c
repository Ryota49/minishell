/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:21:54 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/14 11:13:23 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_pwd(void)
{
	char	cwd[4096];
	char	*res;

	if (getcwd(cwd, sizeof(cwd)))
	{
		res = ft_strdup(cwd);
		return (res);
	}
	else
		return (NULL);
}

static void	change_oldpwd(char **envp)
{
	char	*old_pwd;
	char	*var;

	old_pwd = get_pwd();
	var = ft_strjoin("OLDPWD=", old_pwd);
	change_value(envp, "OLDPWD", var);
	free(old_pwd);
	free(var);
}

static int	cd_too_many_arg(void)
{
	write(2, "cd: too many arguments\n", 23);
	return (1);
}

int	builtin_cd(char **argv, char **envp)
{
	char	*path;

	change_oldpwd(envp);
	if (argv[2])
		return (cd_too_many_arg());
	if (!argv[1])
		path = get_env_value(envp, "HOME");
	else
		path = argv[1];
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

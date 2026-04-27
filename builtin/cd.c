/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:21:54 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/24 14:21:15 by anfouger         ###   ########.fr       */
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

static void	change_oldpwd(t_env *env)
{
	char	*old_pwd;
	char	*var;

	old_pwd = get_pwd();
	var = ft_strjoin("OLDPWD=", old_pwd);
	change_value(env, "OLDPWD", var);
	free(old_pwd);
	free(var);
}

static int	cd_too_many_arg(void)
{
	write(2, "cd: too many arguments\n", 23);
	return (1);
}

static char	*get_path(char **envp, char *argv)
{
	if (!argv)
		return (get_env_value(envp, "HOME"));
	else
		return (get_env_value(envp, "OLDPWD"));
}

int	builtin_cd(char **argv, t_env *env)
{
	char	*path;
	int		flag;

	flag = 0;
	if (argv[2])
		return (cd_too_many_arg());
	if (!argv[1] || ft_strcmp(argv[1], "-"))
	{
		path = get_path(env->envp, argv[1]);
		flag = 1;
	}
	else
		path = argv[1];
	change_oldpwd(env);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	if (flag)
		free(path);
	return (0);
}

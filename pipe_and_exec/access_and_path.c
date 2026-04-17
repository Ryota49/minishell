/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_and_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemonthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 22:30:49 by jemonthi          #+#    #+#             */
/*   Updated: 2026/03/15 04:33:17 by jemonthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/* find the command access and returns the full path if access is OK */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char *resolve_cmd(char *cmd, char **envp)
{
    char **all_path;
    char *path_env;
    char *full_path;
    int i;

    if (!cmd || cmd[0] == '\0')
        return NULL;
    if (ft_strchr(cmd, '/'))
        return ft_strdup(cmd);
    path_env = find_path(envp);
    if (!path_env)
        return NULL;
    all_path = ft_split(path_env, ':');
    if (!all_path)
        return NULL;
    i = 0;
    while (all_path[i])
    {
        full_path = ft_strjoin_three(all_path[i], "/", cmd);
        if (access(full_path, F_OK) == 0) // 👈 IMPORTANT: F_OK pas X_OK ici
            return (ft_free_split(all_path), full_path);
        free(full_path);
        i++;
    }
    return (ft_free_split(all_path), NULL);
}

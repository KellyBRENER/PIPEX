/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:41:58 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/28 17:12:33 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_tabfree(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

//récupère tous les chemins contenu dans PATH
char	**get_allpath(char **env)
{
	char		**tab_allpath;
	char		*str_allpath;
	int			i;
	int			bool;

	i = 0;
	bool = 0;
	tab_allpath = NULL;
	str_allpath = NULL;
	while (env[i] != NULL && bool == 0)
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
		{
			str_allpath = ft_substr(env[i], 5, (size_t)strchr(env[i], '\0'));
			tab_allpath = ft_split(str_allpath, ':');
			free(str_allpath);
			bool = 1;
		}
		i++;
	}
	return (tab_allpath);
}

//teste chaque chemin avec la commande (s'il existe et s'il est executable)
char	*ft_getpath(char *cmd, char **env)
{
	char		**tab_allpath;
	char		*path_cmd;
	int			i;

	i = 0;
	path_cmd = NULL;
	tab_allpath = get_allpath(env);
	while (tab_allpath[i])
	{
		path_cmd = ft_strjoin(tab_allpath[i], cmd);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			ft_tabfree(tab_allpath);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	perror("error command not found or not executable");
	ft_tabfree(tab_allpath);
	return (NULL);
}

//ft_exec execute la commande
int	ft_exec(char *argv, char **env)
{
	char	**ve_cmd;
	char	*cmd_path;
	char	*cmd;

	ve_cmd = ft_split(argv, ' ');
	cmd = ft_strjoin("/", ve_cmd[0]);
	cmd_path = ft_getpath(cmd, env);
	if (cmd_path == NULL)
	{
		free(cmd_path);
		free(cmd);
		ft_tabfree(ve_cmd);
		return (-1);
	}
	execve(cmd_path, ve_cmd, env);
	perror("command execution failed");
	free(cmd_path);
	free(cmd);
	ft_tabfree(ve_cmd);
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:41:58 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/22 17:04:41 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_tabfree(char **tab)
{
	int i;

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
// fonction qui recupere le chemin, le PATH, pour chaque commande et l'integre dans le vecteur
char *ft_getpath(char *cmd, char **env)
{
	char **tab_allpath;
	char *path_cmd;
	char *str_allpath;
	int bool;
	int i;

	i = 0;
	bool = 0;
	str_allpath = NULL;
	tab_allpath = NULL;
	path_cmd = NULL;
	while (env[i] != NULL && bool == 0)
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL) // cherche path dans env
		{
			str_allpath = ft_substr(env[i], 5, (size_t)strchr(env[i], '\0'));
			tab_allpath = ft_split(str_allpath, ':'); // extrait les chemin de env[i] apres PATH= jusqu'au "\n"
			free(str_allpath);
			bool = 1;
		}
		i++;
	}
	i = 0;
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

// fonction qui recupere le vecteur pour chaque commande
// 1. recuperer la commande
// 2. recuperer ce qu'il y a entre "PATH=" et "\n" (l'ensemble des PATH)
// 3. Tester chacun des chemin avec la commande grace a la fonction access
// 4. integrer le chemin trouve dans le vecteur[0]
// 5. integrer le reste des arguments dans le vecteur

// fonction principale qui execute la cmd1 ds le processus enfant et la cmd2 dans le processus parent
int pipex(char **argv, char **env)
{
	int fd[2];
	if (pipe(fd) == -1)
	{
		perror("zsh");
		return -1;
	}
	int pid = fork();
	if (pid == -1)
	{
		perror("zsh");
		return -1;
	}
	if (pid == 0)
	{
		int fd_infile;
		char **ve_cmd;
		char *cmd_path;
		char *cmd;

		fd_infile = open(argv[1], O_RDONLY);
		if (fd_infile == -1)
		{
			//perror("zsh");
			ft_putstr_fd(strerror(errno), 1);
			write(1, ": ", 2);
			ft_putstr_fd(argv[1], 1);
			return -1;
		}
		ve_cmd = ft_split(argv[2], ' ');
		cmd = ft_strjoin("/", ve_cmd[0]);
		dup2(fd_infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(fd_infile);
		cmd_path = ft_getpath(cmd, env);
		execve(cmd_path, ve_cmd, env);
		free(cmd_path);
		free(cmd);
		ft_tabfree(ve_cmd);
		perror("zsh");
		return -1;
	}
	int fd_outfile;
	char **ve_cmd;
	char *cmd_path;
	char *cmd;

	fd_outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_outfile == -1)
	{
		perror("zsh");
		write(1, ": ", 2);
		ft_putstr_fd(argv[4], 1);
		return -1;
	}
	ve_cmd = ft_split(argv[3], ' ');
	cmd = ft_strjoin("/", ve_cmd[0]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_outfile);
	cmd_path = ft_getpath(cmd, env);
	execve(cmd_path, ve_cmd, env);
	free(cmd_path);
	free(cmd);
	ft_tabfree(ve_cmd);
	perror("zsh");
	return -1;
}

/*int main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		write(1, "incorrect argument count", 24);
		return 1;
	}
	if (pipex(argv, env) == -1)
		return 1;
	return (0);
}*/

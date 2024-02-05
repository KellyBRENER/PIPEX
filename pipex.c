/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:41:58 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/05 12:01:50 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

//fonction qui recupere le chemin, le PATH, pour chaque commande et l'integre dans le vecteur
char	*ft_getpath(char *cmd, char **env)
{
	char	**all_path;
	char	*path_cmd;
	int	bool;
	int	i;

	i = 0;
	bool = 0;
	while (env[i] != NULL && bool == 0)
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
		{
			all_path = ft_split(ft_substr(env[i], 5, strchr(env[i], "\n"), ":"));
			bool = 1;
		}
		i++;
	}
	while (all_path[i] && bool == 1)
	{
		if (access)
	}
	path_cmd = ft_split(env, "PATH=")
}

//fonction qui recupere le vecteur pour chaque commande
//1. recuperer la commande
//2. recuperer ce qu'il y a entre "PATH=" et "\n" (l'ensemble des PATH)
//3. Tester chacun des chemin avec la commande grace a la fonction access
//4. integrer le chemin trouve dans le vecteur[0]
//5. integrer le reste des arguments dans le vecteur
char	**ft_getvector(char *str, char **env)
{
	char	*cmd;
	char	**ve_cmd;
	char	*path_cmd;
//soit strlcpy qui copie l-1 char de str (en ayant chercher la position de " " avec strchr en amont)
//soit substr qui alloue de la memoire et copie str de start a len
	ve_cmd = NULL;
	path_cmd = NULL;
	cmd = ft_substr(str, 0, ft_strchr(str, " "));
	path_cmd = ft_getpath(cmd, env)

	ve_cmd = ft_split(str);
	if (!cmd) {
		return NULL;
	}
	path = ft_getpath(cmd, env);
	if (!path) {
		return NULL;
	free(cmd, path_cmd);
	return (ve_cmd);
	}
}

//fonction principale qui execute la cmd1 ds le processus enfant et la cmd2 dans le processus parent
int	pipex(int argc, char **argv, char **env)
{
	int	fd[2];
	if (pipe(fd) == -1)
	{
		ft_printf("error creating pipe");
		return -1;
	}
	int	pid = fork();
	if (pid == -1)
	{
		ft_printf("error creating fork");
		return -1;
	}
	if (pid == 0)
	{
		//child process
		int fd_infile;
		fd_infile = open(argv[1], O_RDONLY);
		if (fd_infile == -1) {
			ft_printf("error opening infile");
			return -1;
		}
		dup2(fd_infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(fd_infile);
		execve(ft_getvector(argv[i], env), env);
		ft_printf("error executing first command");
		return -1;
	}
	//parent process
	int	fd_outfile;
	fd_outfile = open(argv[4], O_WRONLY);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_outfile);
	execve(ft_getvector(argv[3], env), env);
	ft_printf("error executing second command");
	return -1;
}

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		return 4;
	}
	if (pipex(argc, argv, env) == -1)
	{
		return 3;
	};
	return (0);
}

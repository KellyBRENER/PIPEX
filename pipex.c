/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:41:58 by kbrener-          #+#    #+#             */
/*   Updated: 2024/01/18 11:50:28 by kbrener-         ###   ########.fr       */
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
char	*ft_getpath(char **cmd, char **env)
{
	char	**all_path;

	all_path = ft_split("PATH")
}

//fonction qui recupere le vecteur pour chaque commande
char	**ft_getvector(char *str, char **env)
{
	char	**cmd;
	char	*path;

	path = NULL;
	cmd = ft_split(str);
	if (!cmd) {
		return NULL;
	}
	path = ft_getpath(cmd, env);
	if (!path) {
		return NULL;
	}
}

//fonction principale qui execute la cmd1 ds le processus enfant et la cmd2 dans le processus parent
int	pipex(char **argv, int pid, int *fd, char **env)
{
	int	pid2;
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
		execve(ft_getvector(argv[2], env), env);
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
	if (argc != 5)
	{
		return 4;
	}
	int	fd[2];
	if (pipe(fd) == -1)
	{
		return 1;
	}
	int	pid;
	pid = fork();
	if (pid == -1)
	{
		return 2;
	}
	if (pipex(argv, pid, fd, env) == -1)
	{
		return 3;
	};
	return (0);
}

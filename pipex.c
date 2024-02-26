/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:52:15 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/26 15:33:34 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	cmd_child(char **argv, char **env)
{
	int	fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		return (perror("error opening infile"), -1);
	dup2(fd_infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_infile);
	if (ft_exec(argv[2], env) == -1)
		return (perror("error executing first command"), -1);
}

int	cmd_parent(char **argv, char **env)
{
	int	fd_outfile;

	fd_outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_outfile == -1)
		return (perror("error opening outfile"), -1);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_outfile);
	if (ft_exec(argv[3], env) == -1)
		return (perror("error executing second command"), -1);
}

//execute la cmd1 ds le processus enfant et la cmd2 dans le processus parent
int	pipex(char **argv, char **env)
{
	int	fd[2];
	int	pid;

	pid = fork();
	if (pipe(fd) == -1)
		return (perror("error opening pipe"), -1);
	if (pid == -1)
		return (perror("error creating fork"), -1);
	if (pid == 0)
		return (cmd_child(argv, env), -1);
	return (cmd_parent(agrv, env), -1);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		write(1, "incorrect argument count", 24);
		return (1);
	}
	if (pipex(argv, env) == -1)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:52:15 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/29 11:59:28 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parsing(int argc, char **argv)
{
	if (argc != 5)
		return (write(1, "incorrect argument count", 24), -1);
	if (access(argv[1], F_OK) == -1)
		return (perror("no infile or invalid name"), -1);
	if (access(argv[1], R_OK) == -1)
		return (perror("no access to read infile"), -1);
	if (access(argv[4], F_OK) == 0)
	{
		if (access(argv[4], W_OK) == -1)
			return (perror("no access to write in fileout"), 1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int	fd_infile;
	int	fd_outfile;

	if (parsing(argc, argv) == -1)
		return (1);
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		return (perror("error reading infile or no infile to read"), 1);
	fd_outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_outfile == -1)
		return (perror("error opening outfile"), 1);
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	if (ft_fork_and_dup(argv[2], env) == -1)
		return (1);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
	if (ft_exec(argv[3], env) == -1)
		return (1);
	return (0);
}

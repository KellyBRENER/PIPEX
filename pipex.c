/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:52:15 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/27 14:27:15 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	fd_infile;

	i = 2;
	if (argc < 5)
		return (write(1, "incorrect argument count", 24), 1);
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		return (perror("error reading infile or no infile to read"), 1);
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	if (pipex(argc, argv, env, i) == -1)
		return (1);
	return (0);
}

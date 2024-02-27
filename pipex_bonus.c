/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:51:50 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/27 14:31:32 by kbrener-         ###   ########.fr       */
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
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			return (write(1, "incorrect argument count", 24), 1);
		else if (ft_here_doc(argv) == -1)
			return (perror("here_doc don't success"), 1);
		i = 3;
	}
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		return (perror("error reading infile or no infile to read"), 1);
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	if (pipex(argc, argv, env, i) == -1)
		return (1);
	return (0);
}

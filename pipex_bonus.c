/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:51:50 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/29 11:54:15 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*ft_outfile effectue la derniere commande et l'envoie dans le outfile*/
int	ft_outfile(int arg_nbr, char **argv, char **env)
{
	int	fd_out;

	fd_out = open(argv[arg_nbr - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		return (perror("error opening outfile"), -1);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	ft_exec(argv[arg_nbr - 2], env);
	return (-1);
}

/*ft_here_doc cree un fichier here_doc, recupere ce qui est dans l'entree std
et l'ajoute dans here_doc qui sera utilise pour la 1ere commande*/
int	ft_here_doc(char **argv)
{
	char	*line;
	int		fd_heredoc;

	fd_heredoc = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_heredoc == -1)
		return (perror("opening heredoc failed"), -1);
	while (1)
	{
		write(1, "pipe heredoc>", 13);
		line = get_next_line(0);
		if (line == NULL)
			return (close(fd_heredoc), free(line),
				perror("error reading here_doc"), -1);
		if (ft_strlen(line) == (ft_strlen(argv[2]) + 1)
			&& ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_heredoc);
		free(line);
	}
	close(fd_heredoc);
	return (0);
}

//créer une fonction qui boucle jusqu'à la derniere commande
int	pipex(int arg_nbr, char **argv, char **env, int i)
{
	while (i < arg_nbr - 2)
	{
		if (ft_fork_and_dup(argv[i], env) == -1)
			return (-1);
		i++;
	}
	unlink("here_doc");
	if (ft_outfile(arg_nbr, argv, env) == -1)
		return (-1);
	return (-1);
}

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
			return (1);
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

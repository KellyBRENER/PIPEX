/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:41:58 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/26 15:13:11 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*cree la fork et la pipe, attribue la sortie de la commande, execute a commande
puis attribue l'entree de la prochaine commande*/

int	ft_fork_and_dup(char *cmd, char **env)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		return (perror("error creating pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("error creating fork"), -1);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (ft_exec(cmd, env) == -1)
			return (perror("execution of the command failed"), -1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}

//créer une fonction qui boucle jusqu'à la derniere commande
int	pipex_bonus(int arg_nbr, char **argv, char **env, int i)
{
	while (i < arg_nbr - 2)
	{
		if (ft_fork_and_dup(argv[i], env) == -1)
			return (perror("the command cannot be executed"), -1);
		i++;
	}
	if (ft_outfile(arg_nbr, argv, env) == -1)
		return (perror("error executing last command"), -1);
	return (-1);
}

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

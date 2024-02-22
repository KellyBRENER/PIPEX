/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:41:58 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/16 17:14:56 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


//ft_exec execute la commande
int	ft_exec(char *argv, char **env)
{
	char **ve_cmd;
	char *cmd_path;
	char *cmd;

	ve_cmd = ft_split(argv, ' ');
	cmd = ft_strjoin("/", ve_cmd[0]);
	cmd_path = ft_getpath(cmd, env);
	execve(cmd_path, ve_cmd, env);
	free(cmd_path);
	free(cmd);
	ft_tabfree(ve_cmd);
	//changer printf en ft_printf et donc integrer ft_printf dans la libft
    perror("error command cannot be found or no executable");
	return -1;
}

//cree les forks et attribue l'entree et la sortie de chaque commande
int	ft_fork_and_dup(char *cmd, char **env)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("error creating pipe");
		return -1;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("error creating fork");
		return -1;
	}
	if (pid == 0) //child process
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (ft_exec(cmd, env) == -1)
		{
			printf("execution of the command failed");
			return -1;
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return 0;
}

// fonction principale qui cree les fd pour les envoyer dans fork
int pipex_bonus(int arg_nbr, char **argv, char **env)
{
	int fd_in;
	int	fd_out;
	int	i;
//créer une fonction qui ouvre le infile et dup l'entrée standard
	i = 2;
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		perror("error opening infile");
		return -1;
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
//créer une fonction qui boucle jusqu'à la derniere commande
	while (i < arg_nbr - 2)
	{
		if (ft_fork_and_dup(argv[i], env) == -1)
		{
			printf("the commande %s cannot be exec", argv[i]);
			return -1;
		}
		i++;
	}
//créer une fonction qui effectue la derniere commande et l'envoie dans le outfile
	fd_out = open(argv[arg_nbr - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
	{
		perror("error opening outfile");
		return -1;
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	ft_exec(argv[i], env);
	return -1;
}

int	ft_here_doc(int argc, char **argv, char **env)
{
	char *line;
	int	fd_heredoc;

	fd_heredoc = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		write(1, "pipe heredoc>", 13);
		line = get_next_line(0);
		if (line == NULL)
		{
			close(fd_heredoc);
			free(line);
			return -1;
		}
		if (ft_strlen(line) == ft_strlen(argv[2]) && ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, fd_heredoc);
		free(line);
	}
	close(fd_heredoc);
	open(fd_heredoc, O_RDONLY);
	dup2(fd_heredoc, STDIN_FILENO);
	//envoyer dans la boucle qui execute les commandes
	return -1;
}
//doit on verifier que le dernier argument est un nom de fichier et non une commande ?
int main(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		write(1, "incorrect argument count", 24);
		return 1;
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
		{
			write(1, "incorrect argument count", 24);
			return 1;
		}
		else if (ft_here_doc(argc, argv, env) == -1)
		{
			write(1, "here_doc don't success", 22);
			return 1;
		}
	}
	if (pipex_bonus(argc, argv, env) == -1)
		return 1;
	return (0);
}
//pour tester le bonus : < infile grep cat "wc -l" > outfile

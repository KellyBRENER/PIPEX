/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:41:58 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/23 09:41:53 by kbrener-         ###   ########.fr       */
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

/*cree la fork et la pipe, attribue la sortie de la commande, execute a commande
puis attribue l'entree de la prochaine commande*/

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
			perror("execution of the command failed");
			return -1;
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return 0;
}

//créer une fonction qui boucle jusqu'à la derniere commande
int	pipex_bonus(int arg_nbr, char **argv, char **env, int i)
{
	arg_nbr = arg_nbr - i;
	while (i < arg_nbr)
	{
		if (ft_fork_and_dup(argv[i], env) == -1)
		{
			perror("the command cannot be executed");
			return -1;
		}
		i++;
	}
	if (ft_outfile(arg_nbr, argv, env) == -1)
	{
		perror("error executing last command");
		return -1;
	}
	return -1;
}

/*ft_outfile effectue la derniere commande et l'envoie dans le outfile*/

int	ft_outfile(int arg_nbr, char **argv, char **env)
{
	int	fd_out;
	fd_out = open(argv[arg_nbr - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
	{
		perror("error opening outfile");
		return -1;
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	ft_exec(argv[arg_nbr - 2], env);
	return -1;
}

/*ft_here_doc cree un fichier here_doc, recupere ce qui est dans l'entree std
et l'ajoute dans here_doc qui sera utilise pour la 1ere commande*/

int	ft_here_doc(int argc, char **argv, char **env)
{
	char *line;
	int	fd_heredoc;

	fd_heredoc = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		write(1, "pipe heredoc>", 13);
		line = get_next_line(0);
		if (line == NULL) //line doit au moins contenir un "\n"
		{
			close(fd_heredoc);
			free(line);
			perror("error reading here_doc");
			return -1;
		}
		if (ft_strlen(line) == ft_strlen(argv[2]) && ft_strncmp(line, argv[2], ft_strlen(argv[2]) == 0) == 0)
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, fd_heredoc);
		free(line);
	}
	close(fd_heredoc);
	return 0;
}
//doit on verifier que le dernier argument est un nom de fichier et non une commande ?
int main(int argc, char **argv, char **env)
{
	int	i;

	i = 2;
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
			perror("here_doc don't success");
			return 1;
		}
		i = 3;
	}
	int fd_infile;

	if (fd_infile = open(argv[1], O_RDONLY) == -1)
	{
		perror("error reading infile or no infile to read");
		return 1;
	}
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	if (pipex_bonus(argc, argv, env, i) == -1)
		return 1;
	return (0);
}
//pour tester le bonus : < infile grep cat "wc -l" > outfile

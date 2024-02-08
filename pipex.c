/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:41:58 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/08 11:52:10 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void	ft_tabfree(char **tab)
{
	int	i;

	i = 0;
	if (tab) {
		while (tab[i]) {
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}
//fonction qui recupere le chemin, le PATH, pour chaque commande et l'integre dans le vecteur
char	*ft_getpath(char *cmd, char **env)
{
	char	**all_path;
	char	*path_cmd;
	int	bool;
	int	i;

	i = 0;
	bool = 0;
	all_path = NULL;
	path_cmd = NULL;
	while (env[i] != NULL && bool == 0)
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
		{
			all_path = ft_split(ft_substr(env[i], 5, (size_t)strchr(env[i], '\0')), ':'); //extrait les chemin de env[i] apres PATH= jusqu'au "\n"
			bool = 1;
		}
		i++;
	}
	i = 0;
	while (all_path[i]) {
		path_cmd = ft_strjoin(all_path[i], cmd);
		if (access(path_cmd, F_OK | X_OK) == 0) {
			ft_tabfree(all_path);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	ft_tabfree(all_path);
	return (NULL);
}

//fonction qui recupere le vecteur pour chaque commande
//1. recuperer la commande
//2. recuperer ce qu'il y a entre "PATH=" et "\n" (l'ensemble des PATH)
//3. Tester chacun des chemin avec la commande grace a la fonction access
//4. integrer le chemin trouve dans le vecteur[0]
//5. integrer le reste des arguments dans le vecteur

//fonction principale qui execute la cmd1 ds le processus enfant et la cmd2 dans le processus parent
int	pipex(char **argv, char **env)
{
	int	fd[2];
	if (pipe(fd) == -1) {
		perror("error creating pipe");
		return -1;
	}
	int	pid = fork();
	if (pid == -1) {
		perror("error creating fork");
		return -1;
	}
	if (pid == 0) {
		int	fd_infile;
		char	**ve_cmd;

		ve_cmd = ft_split(argv[2], ' ');
		fd_infile = open(argv[1], O_RDONLY);
		if (fd_infile == -1) {
			perror("error opening infile");
			return -1;
		}
		dup2(fd_infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(fd_infile);
		execve(ft_getpath(ft_strjoin("/", ve_cmd[0]), env), ve_cmd, env);
		perror("error executing first command");
		return -1;
	}
	int	fd_outfile;
	char	**ve_cmd;

	ve_cmd = ft_split(argv[3], ' ');
	fd_outfile = open(argv[4], O_WRONLY);
	if (fd_outfile == -1) {
		perror("error opening outfile");
		return -1;
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_outfile);
	execve(ft_getpath(ft_strjoin("/", ve_cmd[0]), env), ve_cmd, env);
	perror("error executing second command");
	return -1;
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
		return (1, write(1, "incorrect argument counts", 25));
	if (pipex(argv, env) == -1)
		return (1, write(1, "pipex execution failed", 22));
	return (0);
}

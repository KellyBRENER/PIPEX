/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:41:58 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/16 11:37:02 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// fonction qui recupere le vecteur pour chaque commande
// 1. recuperer la commande
// 2. recuperer ce qu'il y a entre "PATH=" et "\n" (l'ensemble des PATH)
// 3. Tester chacun des chemin avec la commande grace a la fonction access
// 4. integrer le chemin trouve dans le vecteur[0]
// 5. integrer le reste des arguments dans le vecteur

void ft_tabfree(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

// fonction qui recupere le chemin, le PATH, pour chaque commande et l'integre dans le vecteur
char *ft_getpath(char *cmd, char **env)
{
	char **tab_allpath;
	char *path_cmd;
	char *str_allpath;
	int bool;
	int i;

	i = 0;
	bool = 0;
	str_allpath = NULL;
	tab_allpath = NULL;
	path_cmd = NULL;
	while (env[i] != NULL && bool == 0)
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL) // cherche path dans env
		{
			str_allpath = ft_substr(env[i], 5, (size_t)strchr(env[i], '\0'));
			tab_allpath = ft_split(str_allpath, ':'); // extrait les chemin de env[i] apres PATH= jusqu'au "\n"
			free(str_allpath);
			bool = 1;
		}
		i++;
	}
	i = 0;
	while (tab_allpath[i])
	{
		path_cmd = ft_strjoin(tab_allpath[i], cmd);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			ft_tabfree(tab_allpath);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	ft_tabfree(tab_allpath);
	return (NULL);
}

//ft_exec execute la commande
void	ft_exec(int i, char **argv, char **env)
{
	char **ve_cmd;
	char *cmd_path;
	char *cmd;
	
	ve_cmd = ft_split(argv[i], ' ');
	cmd = ft_strjoin("/", ve_cmd[0]);
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
	cmd_path = ft_getpath(cmd, env);
	execve(cmd_path, ve_cmd, env);
	free(cmd_path);
	free(cmd);
	ft_tabfree(ve_cmd);
	//changer printf en ft_printf et donc integrer ft_printf dans la libft
    printf("Erreur lors de l'execution de la commande : %s\n%s", ve_cmd[0], strerror(errno));
	return -1;
}

//cree les forks et attribue l'entree et la sortie de chaque commande
void	ft_fork_and_dup(int **fd, char **argv, char **env, int arg_nbr)
{
	int	pid;
	int	i;

	i = 2;
	pid = fork();
	if (pid == -1)
	{
		perror("error creating fork");
		return;
	}
	if (pid == 0) //child process
	{
		if (i = 2) //firts cmd
		{
			dup2(fd[0][0], STDIN_FILENO);
			dup2(fd[1][1], STDOUT_FILENO);
		}
		else
		{
			dup2(fd[1][0], STDIN_FILENO);
			dup2(fd[1][1], STDOUT_FILENO);
		}
		ft_exec(i, argv, env); //execute les commandes
	}
	wait(NULL);
	i++;
	if (i < arg_nbr - 2)
		ft_fork_and_dup(fd, argv, env, i);
	dup2(fd[1][0], STDIN_FILENO);
	dup2(fd[0][1], STDOUT_FILENO);
	ft_exec(i, argv, env);
}

// fonction principale qui cree les fd pour les envoyer dans fork
int pipex_bonus(int arg_nbr, char **argv, char **env)
{
	int fd[2][2];//fd[0][0]=infile, fd[0][1]=outfile, fd[1] = pipe
	
	if (pipe(fd[1]) == -1)
	{
		perror("error creating pipe");
		return -1;
	}
	fd[0][0] = open(argv[1], O_RDONLY);
	if (fd[0][0] == -1)
	{
		perror("error opening infile");
		return -1;
	}
	fd[0][1] = open(argv[arg_nbr], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd[0][1] == -1)
	{
		perror("error opening outfile");
		return -1;
	}
	ft_fork_and_dup(fd, argv, env, arg_nbr);
	return 0;
}

//doit on verifier que le dernier argument est un nom de fichier et non une commande ?
int main(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		write(1, "incorrect argument count", 24);
		return 1;
	}
	if (pipex_bonus(argc, argv, env) == -1)
		return 1;
	return (0);
}
//pour tester le bonus : < infile grep cat "wc -l" > outfile
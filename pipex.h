/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:07:06 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/23 09:36:08 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
#include "./libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

char			*ft_getpath(char *cmd, char **env);
void			ft_tabfree(char **tab);
char			*ft_getenv(char *str, char **env);
int				pipex(char **argv, char **env);
int				ft_exec(char *argv, char **env);
int				ft_fork_and_dup(char *cmd, char **env);
int				pipex_bonus(int arg_nbr, char **argv, char **env, int i);
int				ft_outfile(int arg_nbr, char **argv, char **env);
int				ft_here_doc(int argc, char **argv, char **env);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:05:55 by kbrener-          #+#    #+#             */
/*   Updated: 2023/11/16 15:38:06 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;

char			*get_next_line(int fd);
int				next_line(char *buf);
int				len_line(t_list *stash);
int				ft_lstadd_back(t_list **stash, t_list *new);
t_list			*ft_lstnew(char *buf);
int				make_stash(int fd, char *buf, t_list **stash);
int				ft_lstclear(t_list **stash, char *buf);
void			new_content(t_list **stash);
char			*make_line(t_list *stash);
//void			ft_bzero(char *str, int size);

#endif

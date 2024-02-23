/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:32:58 by kbrener-          #+#    #+#             */
/*   Updated: 2023/11/17 09:30:42 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*make_line(t_list *stash)
{
	int			i;
	int			j;
	int			len;
	char		*line;

	line = NULL;
	j = 0;
	i = 0;
	len = len_line(stash);
	if (len == 0)
		return (NULL);
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < len && stash)
	{
		while (stash->content[j] && stash->content[j] != '\n')
			line[i++] = stash->content[j++];
		if (stash->content[j] == '\n')
			line[i++] = '\n';
		j = 0;
		stash = stash->next;
	}
	line[i] = '\0';
	return (line);
}

void	new_content(t_list **stash)
{
	char		*str;
	int			i;
	int			j;

	j = 0;
	i = 0;
	str = NULL;
	if (stash && *stash && (*stash)->content)
	{
		while ((*stash)->content[i] != '\n')
			i++;
		i++;
		while ((*stash)->content[j + i])
			j++;
		str = malloc ((j + 1) * sizeof(char));
		if (!str)
			return ;
		j = 0;
		while ((*stash)->content[i])
			str[j++] = (*stash)->content[i++];
		str[j] = '\0';
		free((*stash)->content);
		(*stash)->content = str;
	}
}

int	ft_lstclear(t_list **stash, char *buf)
{
	t_list	*temp;

	temp = NULL;
	free(buf);
	buf = NULL;
	while (*stash)
	{
		if (next_line((*stash)->content) != 0)
		{
			new_content(stash);
			return (0);
		}
		temp = (*stash)->next;
		free((*stash)->content);
		(*stash)->content = NULL;
		free(*stash);
		*stash = temp;
	}
	if (*stash)
		free(*stash);
	*stash = NULL;
	stash = NULL;
	return (0);
}

int	make_stash(int fd, char *buf, t_list **stash)
{
	int	lu;

	lu = (int)read(fd, buf, BUFFER_SIZE);
	buf[lu] = '\0';
	while (lu)
	{
		ft_lstadd_back(stash, ft_lstnew(buf));
		if (!*stash)
		{
			free(buf);
			buf = NULL;
			return (0);
		}
		if (next_line(buf) == 0)
		{
			lu = (int)read(fd, buf, BUFFER_SIZE);
			buf[lu] = '\0';
		}
		else
			return (1);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char				*line;
	char				*buf;
	static t_list		*stash = NULL;

	line = NULL;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf || fd < 0 || read(fd, buf, 0) < 0 || BUFFER_SIZE <= 0)
	{
		ft_lstclear(&stash, buf);
		return (NULL);
	}
	if (make_stash(fd, buf, &stash))
		line = make_line(stash);
	ft_lstclear(&stash, buf);
	return (line);
}
/*
#include <stdio.h>

int	main(void)
{
	int	fd = open("fichier1.txt", O_RDONLY);
	char	*str = get_next_line(fd);
	while (str)
	{
		printf("%s\n", str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
	return (0);
}*/

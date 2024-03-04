/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:04:55 by kbrener-          #+#    #+#             */
/*   Updated: 2024/02/23 11:19:36 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*void	ft_bzero(char *str, int size)
{
	int			i;

	i = 0;
	while (i <= size)
		str[i++] = '\0';
	return ;
}
*/
t_list	*ft_lstnew_gnl(char *buf)
{
	t_list		*lst;
	int			i;

	i = 0;
	lst = NULL;
	lst = malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->content = malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!lst->content)
	{
		free(lst);
		lst = NULL;
		return (NULL);
	}
	while (buf[i] != '\0')
	{
		lst->content[i] = buf[i];
		i++;
	}
	lst->content[i] = '\0';
	lst->next = NULL;
	return (lst);
}

int	ft_lstadd_back_gnl(t_list **stash, t_list *new)
{
	t_list	*temp;

	temp = *stash;
	if (stash && new)
	{
		if (*stash != NULL)
		{
			while ((*stash)->next != NULL)
				*stash = (*stash)->next;
			(*stash)->next = new;
			*stash = temp;
			return (1);
		}
		*stash = new;
		return (1);
	}
	return (0);
}

int	len_line(t_list *stash)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (stash)
	{
		while (stash->content[i] != '\0' && stash->content[i] != '\n')
		{
			i++;
			len++;
		}
		if (stash->content[i] == '\0')
		{
			stash = stash->next;
			i = 0;
		}
		else if (stash->content[i] == '\n')
			return (len + 1);
	}
	return (len);
}

int	next_line(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		return (1);
	return (0);
}

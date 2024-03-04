/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:55:54 by kbrener-          #+#    #+#             */
/*   Updated: 2023/10/16 14:25:08 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del || !*lst)
		return ;
	while (lst && lst[0])
	{
		temp = lst[0]->next;
		ft_lstdelone(lst[0], del);
		lst[0] = temp;
	}
	lst[0] = NULL;
}

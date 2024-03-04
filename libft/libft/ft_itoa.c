/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:53:07 by kbrener-          #+#    #+#             */
/*   Updated: 2023/11/17 14:59:08 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_nb(long int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		i++;
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		nb;
	int				count_nb;

	nb = (long)n;
	count_nb = ft_count_nb(nb);
	str = malloc((count_nb + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[count_nb] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--count_nb] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}

/*
#include <unistd.h>

int	main(void)
{
	int	n = 0;
	char	*nb = ft_itoa(n);
	int	i = 0;

	while (nb[i])
	{
		write(1, &nb[i], 1);
		i++;
	}
}*/

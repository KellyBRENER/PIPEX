/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:18:47 by kbrener-          #+#    #+#             */
/*   Updated: 2023/11/24 14:27:10 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putcharp(char c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_putnbrp(int n, int *count_char)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		*count_char = *count_char + ft_putcharp('-');
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbrp(nb / 10, count_char);
	*count_char = *count_char + ft_putcharp((nb % 10) + '0');
	return ;
}

int	ft_strlenp(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*pour convertir un nombre decimal en n'importe quelle base non signee*/

void	ft_putnbr_basep(long int nb, char *base, int *count_char)
{
	long int			lenght_base;

	lenght_base = ft_strlenp(base);
	if (nb < 0)
		nb = -nb;
	if (nb > (lenght_base - 1))
		ft_putnbr_basep((nb / lenght_base), base, count_char);
	*count_char = *count_char + ft_putcharp(base[(nb % lenght_base)]);
}

int	ft_putstrp(const char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		ft_putcharp(str[i]);
		i++;
	}
	return (i);
}

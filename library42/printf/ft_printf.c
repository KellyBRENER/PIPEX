/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:10:41 by kbrener-          #+#    #+#             */
/*   Updated: 2023/11/24 15:01:00 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/* il faut gerer c: argument de type int converti en unsigned char, 
s: argument de type const char *,
p: affiche un pointeur, 
d: argument de type int converti en chiffre decimal signe,
i: permet d'afficher un nombre signe en decimal (interprete l'octal (O) 
et l'hexadecimal (Ox))
u: affiche un entier non signe en decimal,
xX: argument unsigned int converti en chiffre hexadecimal non signe 
(x (abcdef) et X (ABCDEF)), 
%: pour ecrire un %*/

void	ft_pos(long long nb, char *base, int *count_char)
{
	if (nb == 0)
	{
		*count_char += ft_putstrp("(nil)");
		return ;
	}
	else
	{
		*count_char += ft_putstrp("0x");
		ft_position(nb, base, count_char);
	}
}

void	ft_position(long long nb, char *base, int *count_char)
{
	long long			lenght_base;

	lenght_base = ft_strlenp(base);
	if (nb < 0)
		nb = -nb;
	if (nb > (lenght_base - 1))
		ft_position((nb / lenght_base), base, count_char);
	*count_char = *count_char + ft_putcharp(base[(nb % lenght_base)]);
}

void	ft_cond(char c, va_list args, int *nbc)
{
	char	*hexalower;
	char	*hexaupper;

	hexalower = "0123456789abcdef";
	hexaupper = "0123456789ABCDEF";
	if (c == 's')
		*nbc += ft_putstrp(va_arg(args, const char *));
	if (c == 'd' || c == 'i')
		ft_putnbrp(va_arg(args, int), nbc);
	if (c == 'c')
		*nbc += ft_putcharp(va_arg(args, int));
	if (c == 'x')
		ft_putnbr_basep(va_arg(args, unsigned int), hexalower, nbc);
	if (c == 'X')
		ft_putnbr_basep(va_arg(args, unsigned int), hexaupper, nbc);
	if (c == 'u')
		ft_putnbr_basep(va_arg(args, unsigned int), "0123456789", nbc);
	if (c == 'p')
		ft_pos(va_arg(args, unsigned long long), hexalower, nbc);
	if (c == '%')
		*nbc += ft_putcharp(c);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;
	int			nbc;

	i = 0;
	nbc = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			ft_cond(format[i], args, &nbc);
		}
		else
			nbc += ft_putcharp(format[i]);
		i++;
	}
	va_end(args);
	return (nbc);
}

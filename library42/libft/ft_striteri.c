/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:53:39 by kbrener-          #+#    #+#             */
/*   Updated: 2023/10/11 11:27:22 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*void	ft_capitalize(unsigned int i, char *s)
{
	if ('a' <= s[i] && s[i] <= 'z')
		s[i] = s[i] - 32;
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <unistd.h>

int	main(void)
{
	char	s[] = "bonjour";
	int	i = 0;

	ft_striteri(s, &ft_capitalize);
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}*/

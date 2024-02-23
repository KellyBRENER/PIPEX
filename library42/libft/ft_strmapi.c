/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:20:11 by kbrener-          #+#    #+#             */
/*   Updated: 2023/10/09 14:38:48 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
/*
char	ft_oneup(unsigned int pos, char c)
{
	c = c + 1 + pos - pos;
	return (c);
}*/

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
#include <unistd.h>

int	main(void)
{
	char	*dest;
	int	i = 0;
	const char	*str = "bonjour";

	dest = ft_strmapi(str, &ft_oneup);
	while (dest[i])
	{
		write(1, &dest[i], 1);
		i++;
	}
}*/

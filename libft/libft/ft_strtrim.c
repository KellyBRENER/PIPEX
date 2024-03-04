/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:31:17 by kbrener-          #+#    #+#             */
/*   Updated: 2023/10/11 16:31:16 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ifset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_len(char const *s1, char const *set)
{
	int	i;
	int	len;

	i = 0;
	while (s1[i] && ft_ifset(s1[i], set) == 1)
		i++;
	len = i;
	while (s1[i])
		i++;
	i--;
	while (s1[i] && ft_ifset(s1[i], set) == 1)
		i--;
	len = i - len;
	return (len + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*trims1;

	i = 0;
	len = ft_len(s1, set);
	while (s1[i] && ft_ifset(s1[i], set) == 1)
		i++;
	trims1 = ft_substr(s1, i, len);
	return (trims1);
}
/*
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*str;
	int	n = 1;
	int	i = 0;

	if (argc != 3)
		return (0);
	str = ft_strtrim(argv[n], argv[n + 1]);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;	
	}
}*/

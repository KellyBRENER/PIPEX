/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:20:26 by kbrener-          #+#    #+#             */
/*   Updated: 2023/10/12 15:04:16 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		i = 0;
		while (i < (int)n)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i++;
		}
	}
	else
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i--;
		}
	}
	return (dest);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	size_t	size = 4;
	void	*dest = "monsieur";
	const void	*src = "bonjour";
	char	*result;
	int	i = 0;

	result = (char *)memmove(dest, src, size);
	while (result[i])
	{
		write(1, &result[i], 1);
		i++;
	}
}*/

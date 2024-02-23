/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:44:07 by kbrener-          #+#    #+#             */
/*   Updated: 2023/10/10 10:50:20 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (1);
	else
		return (0);
}
/*
#include <unistd.h>
#include <ctype.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	if (ft_isascii(argv[1][0]) == isascii(argv[1][0]))
		write(1, "test ok", 7);
	else
		write(1, "error", 5);
}*/

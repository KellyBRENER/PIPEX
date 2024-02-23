/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:07:06 by kbrener-          #+#    #+#             */
/*   Updated: 2023/11/24 15:01:31 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

void	ft_cond(char c, va_list args, int *nbc);
int		ft_printf(const char *format, ...);
int		ft_putcharp(char c);
void	ft_putnbrp(int n, int *count_char);
int		ft_strlenp(char *str);
void	ft_putnbr_basep(long int nb, char *base, int *count_char);
int		ft_putstrp(const char *str);
void	ft_position(long long nb, char *base, int *count_char);
void	ft_pos(long long nb, char *base, int *count_char);

#endif

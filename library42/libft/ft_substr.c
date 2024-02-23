/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:12:14 by kbrener-          #+#    #+#             */
/*   Updated: 2023/10/12 10:18:44 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	size;
	size_t			i;

	size = ft_strlen(s);
	if (size < start)
		len = 0;
	else if (len > (size - start))
		len = size - start;
	substr = (char *)malloc((len + 1) * sizeof(*s));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (start + i < size && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

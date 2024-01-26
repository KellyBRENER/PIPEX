/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:41:58 by kbrener-          #+#    #+#             */
/*   Updated: 2024/01/18 12:02:04 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

int	main(int argc, char **argv, char **env)
{
	if (!argc) {
		return 1;
	}
	if (!argv) {
		return 2;
	}
	int	i = 0;
	while (env[i]) {
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

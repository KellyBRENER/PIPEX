/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrener- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:41:58 by kbrener-          #+#    #+#             */
/*   Updated: 2024/01/08 11:26:22 by kbrener-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("example.txt", O_RDONLY);

    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Duplique le descripteur de fichier
    int new_fd = dup(fd);

    if (new_fd == -1) {
        perror("Erreur lors de la duplication du descripteur de fichier");
        close(fd);
        return 1;
    }

    printf("Descripteur de fichier d'origine : %d\n", fd);
    printf("Nouveau descripteur de fichier : %d\n", new_fd);

    // Vous pouvez maintenant utiliser fd et new_fd pour lire depuis le fichier.

    // N'oubliez pas de fermer les descripteurs de fichier lorsqu'ils ne sont plus nécessaires.
    close(fd);
    close(new_fd);

    return 0;
}



#include <stdio.h>

extern char **environ;

int main() {
    // Afficher toutes les variables d'environnement
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    return 0;
}

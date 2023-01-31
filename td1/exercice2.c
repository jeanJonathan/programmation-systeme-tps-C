#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define N 1000000  // Taille du tableau
int main()
{
    int tab[N];  // Tableau d'entiers
    int valeur;  // Valeur à rechercher
    // Initialisation du tableau (à remplacer par la lecture d'un fichier)
    for (int i = 0; i < N; i++)
        tab[i] = i;
    printf("Entrez la valeur à rechercher : ");
    scanf("%d", &valeur);

    pid_t pid = fork();
    if (pid == -1)
    { // Erreur lors de la création du processus fils
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    { // Processus fils
        for (int i = N / 2; i < N; i++)
        {
            if (tab[i] == valeur)
            {
                printf("Le fils a trouvé en position : %d\n", i);
                exit(EXIT_SUCCESS);
            }
        }
        printf("La valeur n'a pas été trouvée par le fils\n");
        exit(EXIT_SUCCESS);
    }
    else
    {// Processus père
        for (int i = 0; i < N / 2; i++)
        {
            if (tab[i] == valeur)
            {
                printf("Le père a trouvé en position : %d\n", i);
                exit(EXIT_SUCCESS);
            }
        }
        printf("La valeur n'a pas été trouvée par le père\n");
        // Attente de la terminaison du processus fils
        int status;
        waitpid(pid, &status, 0);
    }
    return 0;
}

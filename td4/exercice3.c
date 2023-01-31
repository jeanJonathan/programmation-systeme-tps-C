#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define N 1000000  // Taille du tableau

//Fonction pour traiter le signal USR1
void signal_handler(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("La valeur a été trouvée par l'autre processus. Arrêt de la recherche...\n");
        exit(0);
    }
}
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
        signal(SIGUSR1, signal_handler);
        for (int i = N / 2; i < N; i++)
        {
            if (tab[i] == valeur)
            {
                printf("Le fils a trouvé en position : %d\n", i);
                kill(getppid(), SIGUSR1);
                exit(EXIT_SUCCESS);
            }
        }
        printf("La valeur n'a pas été trouvée par le fils\n");
        exit(EXIT_SUCCESS);
    }
    else
    {// Processus père
        signal(SIGUSR1, signal_handler);
        for (int i = 0; i < N / 2; i++)
        {
            if (tab[i] == valeur)
            {
                printf("Le père a trouvé en position : %d\n", i);
                kill(pid, SIGUSR1);
                exit(EXIT_SUCCESS);
            }
        }
        printf("La valeur n'a pas été trouvée par le père\n");
    }
    return 0;
}

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 1000000  // Taille du tableau

int tab[N];  // Tableau d'entiers
int valeur;  // Valeur à rechercher
int position = -1;  // Position où la valeur a été trouvée (initialisée à -1 pour indiquer qu'elle n'a pas encore été trouvée)
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex pour protéger la variable "position"
// Fonction exécutée par le premier thread
void* recherche1(void* arg)
{ // Recherche de la valeur dans la 1ère moitié du tableau
    for (int i = 0; i < N / 2; i++)
    {
        if (tab[i] == valeur)
        {
            // Mise à jour de la variable "position"
            pthread_mutex_lock(&mutex);
            position = i;
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    pthread_exit(NULL);
}
// Fonction exécutée par le second thread
void* recherche2(void* arg)
{ // Recherche de la valeur dans la 2ème moitié du tableau
    for (int i = N / 2; i < N; i++)
    {
        if (tab[i] == valeur)
        {
            // Mise à jour de la variable "position"
            pthread_mutex_lock(&mutex);
            position = i;
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    pthread_exit(NULL);
}
int main()
{ // Initialisation du tableau (à remplacer par la lecture d'un fichier)
    for (int i = 0; i < N; i++)
        tab[i] = i;
    printf("Entrez la valeur à rechercher : ");
    scanf("%d", &valeur);
    pthread_t thread1, thread2;  // Identifiants des threads
    // Création des threads
    int ret1 = pthread_create(&thread1, NULL, recherche1, NULL);
    int ret2 = pthread_create(&thread2, NULL, recherche2, NULL);
    if (ret1 != 0 || ret2 != 0)
    {
        fprintf(stderr, "Erreur lors de la création des threads\n");
        exit(EXIT_FAILURE);
    }
    // Attente de la terminaison des threads
    if (pthread_join(thread1, NULL) != 0 || pthread_join(thread2, NULL) != 0)
    {
        fprintf(stderr, "Erreur lors de l'attente de la terminaison des threads\n");
        exit(EXIT_FAILURE);
    }
    // Affichage du résultat
    if (position == -1)
        printf("La valeur n'a pas été trouvée\n");
    else
        printf("La valeur a été trouvée en position : %d\n", position);
    return 0;
}


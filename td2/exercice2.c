#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000000 // Taille du tableau

int max = 0; // Variable globale pour stocker le maximum
int array[N]; // Tableau d'entiers
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Sémaphore de type mutex

void* find_max(void* arg) {
    int start = *((int*)arg); // Début de la partie du tableau à traiter
    int end = start + N / 2; // Fin de la partie du tableau à traiter
    // Recherche du maximum dans la partie du tableau assignée au thread
    for (int i = start; i < end; i++) {
        pthread_mutex_lock(&mutex); // Verrouillage du mutex
        if (array[i] > max) {
            max = array[i];
        }
        pthread_mutex_unlock(&mutex); // Déverrouillage du mutex
    }
    return NULL;
}
int main(void) {
    // Initialisation du tableau avec des valeurs aléatoires
    for (int i = 0; i < N; i++) {
        array[i] = rand(); // Initialisation du tableau des valeurs aleatoires
    }
    // Création des threads
    pthread_t thread1, thread2;
    int start1 = 0;
    int start2 = N / 2;
    pthread_create(&thread1, NULL, find_max, &start1);
    pthread_create(&thread2, NULL, find_max, &start2);
    // Attente de la fin des threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    // Affichage du résultat
    printf("Max: %d\n", max);
    return 0;
}

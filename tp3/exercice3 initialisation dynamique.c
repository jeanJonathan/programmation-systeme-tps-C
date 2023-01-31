#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

unsigned long cpt = 0;
pthread_mutex_t mutex; // mutex pour protéger la variable cpt

void* compter_function(void* arg) {
    for (int i = 0; i < 10000000; i++)
    {
        // verrouillage du mutex
        pthread_mutex_lock(&mutex);

        // mise à jour de la variable cpt
        int tmp = cpt;
        tmp++;
        cpt = tmp;

        // déverrouillage du mutex
        pthread_mutex_unlock(&mutex);
    }
    printf("%lu", cpt);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // initialisation du mutex
    pthread_mutex_init(&mutex, NULL);

    // création des threads
    pthread_create(&thread1, NULL, compter_function, NULL);
    pthread_create(&thread2, NULL, compter_function, NULL);

    // attente de la fin des threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // affichage de la valeur finale du compteur
    printf("Valeur finale du compteur %lu\n", cpt);

    // destruction du mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

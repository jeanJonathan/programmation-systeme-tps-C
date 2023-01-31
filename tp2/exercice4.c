#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // pour sleep

void* thread_function1(void* arg)
{
    while (1) // boucle infinie
    {
        printf(".\n");
        sleep(1); // pause de 1 seconde
    }
    return NULL;
}
void* thread_function2(void* arg)
{
    printf("Tapez un caractère : ");
    char c = getchar(); // attend un caractère au clavier
    printf("Caractère reçu : %c\n", c);
    return NULL;
}
int main(void)
{
    pthread_t thread1, thread2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);// initialisation des attributs
    // préparation des attributs pour créer les threads détachés
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    // création des deux threads
    pthread_create(&thread1, &attr, thread_function1, NULL);
    pthread_create(&thread2, &attr, thread_function2, NULL);
    printf("Les 2 threads sont lancés\n");
   
    pthread_join(thread2, NULL);
    printf("On va s'arrêter là\n");
    return 0;
}


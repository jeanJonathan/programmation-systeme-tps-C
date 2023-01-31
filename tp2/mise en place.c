#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_non_fin_execution(void* arg)
{
    printf("Thread 1 exécutant la fonction thread_non_fin_execution\n");
    sleep(3); /*Afin de ne pas voir l'execution de la suite a l'ecran 
    du coup l'execution de cette fonction se fera en arriere plan*/
    printf("Thread 1 terminé\n");
    printf("Pourquoi as tu attendu la fin de mon execution\n");
    return NULL;
}
void* thread_fin_execution(void* arg)
{
    printf("Thread 2 exécutant la fonction thread_fin_execution\n");
    sleep(1);
    printf("Thread 2 terminé\n");
    printf("Merci d'avoir attendu la fin de mon execution\n");
    return NULL;
}
int main(int argc, char* argv[])
{
    pthread_t thread1, thread2;
    int status;
    status = pthread_create(&thread1, NULL, thread_non_fin_execution, NULL);
    if (status1 != 0) {
        perror("Erreur lors de la création du thread 1");
        exit(EXIT_FAILURE);
    }
    status = pthread_create(&thread2, NULL, thread_fin_execution, NULL);
    if (status != 0) {
        perror("Erreur lors de la création du thread 2");
        exit(EXIT_FAILURE);
    }
    status = pthread_detach(thread1);
    if (status != 0) {
        perror("Erreur lors de la détachement du thread 1");
        exit(EXIT_FAILURE);
    }
    printf("Thread 1 détaché\n");
    status = pthread_join(thread2, NULL);
    if (status != 0) {
        perror("Erreur lors de l'attente de la fin du thread 2");
        exit(EXIT_FAILURE);
    }
    return 0;
}


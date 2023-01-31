#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 1000000

int main() {
    int i;
    int sum = 0;
    int array[N];
    // Initialisez le tableau avec des valeurs
    for (i = 0; i < N; i++) {
        array[i] = i;
    }
    // Créez un tube
    int pipefd[2]; // tableau de descripteur de fichier
    int ret = pipe(pipedf);
    if (ret == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    // Créez un processus fils
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        // Fermez la lecture du tube dans le fils
        close(pipefd[0]);
        // Calculez la somme des éléments de la première moitié du tableau
        int sum = 0;
        for (i = 0; i < N / 2; i++) {
            sum += array[i];
        }
        // Écrivez la somme dans le tube
        write(pipefd[1], &sum, sizeof(sum));
        // Fermez l'écriture du tube dans le fils
        close(pipefd[1]);
        // Terminez le fils
        exit(EXIT_SUCCESS);
    }
    else {
        // Fermez l'écriture du tube dans le père
        close(pipefd[1]);
        // Calculez la somme des éléments de la seconde moitié du tableau
        for (i = N / 2; i < N; i++) {
            sum += array[i];
        }
        // Lisez la somme envoyée par le fils dans le tube
        int child_sum;
        read(pipefd[0], &child_sum, sizeof(child_sum));
        // Fermez la lecture du tube dans le père
        close(pipefd[0]);
        // Ajoutez la somme du fils à la somme du père pour obtenir la somme finale
        sum += child_sum;
        // Attendre la terminaison du fils
        wait(NULL); // ou waitpid(pid,&status,0)
        // Affichez le résultat final
        printf("Sum: %d\n", sum);
        exit(EXIT_SUCCESS);
    }

    return 0;
}

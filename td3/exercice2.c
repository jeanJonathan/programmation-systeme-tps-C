#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1
int lireWav(int* right, int* left) {
    // Implémentation de la fonction de lecture du fichier wav
    // Place la valeur de l'échantillon pour la voie droite dans right et celle de la voie gauche dans left
    // Retourne 1 si le fichier est fini, 0 sinon
    return 0;
}
int main(int argc, char* argv[]) {
    int right, left;
    int pipe_left[2], pipe_right[2];
    // Création des tubes
    if (pipe(pipe_left) == -1 || pipe(pipe_right) == -1) {
        perror("Erreur lors de la création des tubes");
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    // Création du processus fils
    pid = fork();
    if (pid < 0) {
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        // Processus père
        close(pipe_left[READ]);
        close(pipe_right[WRITE]);

        while (lireWav(&right, &left) == 0) {
            // Envoi de la valeur de la voie gauche au processus fils
            write(pipe_left[WRITE], &left, sizeof(int));

            // Traitement de la valeur de la voie droite
        }
        // Envoi de -1 au processus fils pour indiquer la fin du fichier
        left = -1;
        write(pipe_left[WRITE], &left, sizeof(int));
        close(pipe_left[WRITE]);

        // Réception du max et de la moyenne calculés par le processus fils
        int max, average;
        read(pipe_right[READ], &max, sizeof(int));
        read(pipe_right[READ], &average, sizeof(int));
        close(pipe_right[READ]);

        // Affichage des valeurs obtenues
        printf("Max voie gauche : %d\n", max);
        printf("Moyenne voie gauche : %d\n", average);

        // Attente de la terminaison du processus fils
        wait(NULL);
    }
    else {
        // Processus fils
        close(pipe_left[WRITE]);
        close(pipe_right[READ]);
        int value, sum = 0, count = 0;
        int max = 0;
        while (true) {
            // Réception des valeurs envoyées par le processus père
            read(pipe_left[READ], &value, sizeof(int));
            if (value == -1) {
                // Fin du fichier
                break;
            }

            // Mise à jour du max et du total des échantillons reçus
            if (value > max) {
                max = value;
            }
            sum += value;
            count++;
        }
        close(pipe_left[READ]);
        // Calcul de la moyenne
        int average = sum / count;
        // Envoi du max et de la moyenne au processus père
        write(pipe_right[WRITE], &max, sizeof(int));
        write(pipe_right[WRITE], &average, sizeof(int));
        close(pipe_right[WRITE]);
    }

    return 0;
}


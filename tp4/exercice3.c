#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define BUFFER_SIZE 100

int main(int argc, char* argv[]) {
	int pipedf[2];
	int ret = pipe(pipedf);
	if (ret ==-1) {
		//erreur
		perror("Erreur lors de la creation du tube");
		exit(EXIT_FAILURE);
	}
	pid_t pid = fork();
	if (pid == -1) {
		perror("Erreur lors de la création du processus fils");
		exit(EXIT_FAILURE);
	}
    if (pid == 0) {
        // Processus fils
        // Fermeture de l'extrémité d'écriture du tube (inutile pour le fils)
        close(pipefd[1]);

        // Lecture du tube jusqu'à la fin de la transmission
        while (read(pipefd[0], buffer, BUFFER_SIZE) > 0) {
            // Mise en majuscule des caractères lus
            for (int i = 0; i < BUFFER_SIZE; i++) {
                buffer[i] = toupper(buffer[i]);
            }
            // Affichage des caractères mis en majuscule
            printf("%s", buffer);
        }

        // Fermeture de l'extrémité de lecture du tube (important !)
        close(pipefd[0]);

        exit(EXIT_SUCCESS);
    }
    else {
        // Processus père
        // Fermeture de l'extrémité de lecture du tube (inutile pour le père)
        close(pipefd[0]);

        // Lecture des caractères au clavier et écriture dans le tube
        char c;
        while ((c = getchar()) != EOF) {
            write(pipefd[1], &c, 1);
        }
        // Envoi du signal EOF au fils pour lui signaler la fin de la transmission
        write(pipefd[1], &c, 1);

        // Fermeture de l'extrémité d'écriture du tube (important !)
        close(pipefd[1]);

        // Attente de la fin du fils
        wait(NULL);

        printf("fin de transfert\n");

        exit(EXIT_SUCCESS);
    }
    /*N:B: Le processus père envoie le signal EOF au fils en écrivant
    un octet nul dans le tube. Le fils doit s'arrêter lorsqu'il lit un octet nul
    dans le tube, et fermer l'extrémité de lecture du tube.*/
	
	return 0;
}
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
		//erreur
		perror("Erreur lors de la création du processus fils");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		//fils
		//Fermeture du descripteur d'ecriture 1
		close(pipedf[1]);

		// Lecture du tube jusqu'à la fin de la transmission
		char buffer[BUFFER_SIZE]; // tampon pour la lecture et l'écriture dans le tube
		while (read(pipefd[0], buffer, BUFFER_SIZE) > 0) {
			// Mise en majuscule des caractères lus
			for (int i = 0; i < BUFFER_SIZE; i++) {
				buffer[i] = toupper(buffer[i]);
			}
			// Affichage des caractères mis en majuscule
			printf("%s", buffer);
		}
		//Fermeture du descripteur de lecture 0 
		close(pipedf[0]);
		exit(EXIT_SUCCESS);
	}
	else {
		//pere
		// Fermeture du descripteur de lecture 0
		close(pipedf[0]);
		// Ecriture dans le tube
		char c;
		// Tant qu'un caractere est recu du clavier et qu'il est different de $
		while ((c = getchar() != '$'))
		{
			// Ecriture du caractere dans le tube
			write(pipefd[1], &c, 1);
		}
		//Envoi du caractère '$' au fils pour lui signaler la fin de la transmission
		write(pipefd[1], &c, 1);

		//fermeture du descripteur d'ecriture 1
		close(pipedf[1]);

		//Attente du fils (important !)
		wait(NULL);

		exit(EXIT_SUCCESS);
	}
	return 0;



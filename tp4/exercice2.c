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
		close(pipedf[1]);

		char buffer[BUFFER_SIZE]; 
		/*Si read retourne 0, cela signifie que le tube a été fermé par 
		l'autre extrémité, et donc que le processus père a terminé 
		l'envoi de données.*/
		while (read(pipefd[0], &c, 1) > 0) {
			// Mise en majuscule des caractères lus
			c = toupper(c);
			printf("%s",c);
		}
		close(pipedf[0]);
		exit(EXIT_SUCCESS);
	}
	else {

		close(pipedf[0]);
		// Ecriture dans le tube
		char c;
		while ((c = getchar() != '$'))
		{
			// Ecriture du caractere dans le tube
			write(pipefd[1], &c, 1);
		}
		write(pipefd[1], &c, 1);

		close(pipedf[1]);

		//Attente du fils (important !)
		wait(NULL);

		exit(EXIT_SUCCESS);
	}
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int pipefd[2]; // tableau de descripteurs de fichier pour le tube
	int ret = pipe(pipefd); // création d'un tube anonyme
	if (ret == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) { // processus fils
		close(pipefd[0]); // fermeture du descripteur de fichier de lecture
		const char* message = "Bonjour, je suis le processus fils !";
		write(pipefd[1], message, strlen(message)); // écriture du message dans le tube
		close(pipefd[1]); // fermeture du descripteur de fichier d'écriture
	}
	else { // processus père
		close(pipefd[1]); // fermeture du descripteur de fichier d'écriture
		char buffer[1024];
		ssize_t nbytes = read(pipefd[0], buffer, sizeof(buffer)); // lecture du contenu du tube
		buffer[nbytes] = '\0'; // ajout d'un caractère de fin de chaîne
		printf("Message reçu dans le processus père : %s\n", buffer);
		close(pipefd[0]); // fermeture du descripteur de fichier de lecture
	}
	/* Remarque on pouvais fermer le descripteur de fichier ici et non dans le if
	mais c'est qu'en meme bien de le faire dans le if */
	return 0;

}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*exemple complet de code qui utilise un tube de processus pour lire 
les résultats de la commande "ls -l" dans le processus père*/
int main() {

	//1-Creation d'un tube avec la fonction pipe()
	int pipedf[2];
	int ret = pipe(pipedf);
	if (ret == -1) {
		perror("pipe");
		exit(EXIT_FAILLURE);
	}
	//2- Creation d'un processus fils
	pip_t pid = fork();
	if (pid ==-1) {
		perror("fork");
		exit(EXIT_FAILLURE);
	}
	printf("Descriteur de fichier de lecture pipedf[0] ouvert (Sortie)--ok\n")
	printf("Descriteur de fichier d'ecriture pipedf[1] ouvert(entree)--ok\n");
	printf("Duplication du processus--ok\n")

	/*3-Pour assurer la communication, on ferme le descripteur de fichier de lecture
	( de la sortie du tube pipedf[0] ) dans le processus fils*/

	if (pip == 0) {
			close(pipe[0]);// fermeture du descripteur de fichier de lecture
			dup2(pipe[1], STDOUT_FILENO); // redirection de la sortie standard vers le descripteur de fichier d'écriture
			execlp("ls", "ls", "-l", NULL); // exécution de la commande "ls -l"
	}
	/*4- Dans le processus père, on utilise la fonction close() pour fermer le 
	descripteur de fichier d'écriture du tube (pipefd[1]) et utiliser la
	fonction read() pour lire les données envoyées par le processus fils*/
	else {
		close(pipedf[1]); // fermeture du descripteur de fichier d'écriture
		char buffer[1024];
		ssize_t nbytes;
		while ((nbytes = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
			write(STDOUT_FILENO, buffer, nbytes);
		}

	}
	/*5-Utiliser la fonction close() pour fermer les descripteurs de fichier 
	du tube dans les deux processus : 
	close(pipefd[0]);close(pipefd[1]);*/
	close(pipefd[0]);
	close(pipefd[1]);

	return 0;
}
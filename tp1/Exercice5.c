#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h> 
#include <sys/wait.h> 
int main(int argc, char* argv[]) { /*Il nous revient a modifier les parametre du 
	main*/
	
// On doit donc vérifier qu'au moins un paramètre a été fourni
	if (argc < 2) {
		fprintf(stderr, "Erreur : veuillez fournir au moins un paramètre\n");
		return 1;
	}
	pid_t pid = fork();
	int status;
	if (pid != 0) {
		wait(&status);// attend la fin du processus fils
		printf("La valeur retourner par mon fils est %d\n",WEXITSTATUS(status));

	else {

		if (pid == -1) {
			printf("Error");
			exit(1);
		}
		// Execution de la commande unix ps
		/* le premier paramètre est la commande à exécuter, les autres sont ses
		arguments*/
		execvp(argv[1], argv + 1);

		exit(EXIT_FAILURE);// quitte le processus en cas d'erreur
	}
	return 0;
}
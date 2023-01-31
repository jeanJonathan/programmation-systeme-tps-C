#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h> 
#include <sys/wait.h> 
int main() {

	pid_t pid = fork();
	int status;/*déclare une variable pour stocker le statut de retour 
	du processus fils*/
	if (pid != 0) {
		wait(&status);// attend la fin du processus fils
		printf("La valeur retourner par mon fils est %d\n",WEXITSTATUS(status));

	else {

		if (pid == -1) {
			printf("Error");
			exit(1);
		}
		// Execution de la commande unix ps
		execl("/usr/bin/ps", "ps", NULL);/* Ici on devrais ensuite preciser le chemin
		sinon il y aurait une erreur en remplacant execlp par execl */

		exit(EXIT_FAILURE);// quitte le processus en cas d'erreur
	}
	return 0;

}
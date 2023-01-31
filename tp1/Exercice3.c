#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h> /*pour utiliser pid_t et size_t(pour stocker tailles 
de mémoire)*/
#include <sys/wait.h> /*Pour utililser les macros wait, WEXITSTATUS..pour attendre 
ou reccuperer les information sur le status des processus*/
int main() {
	pid_t pid = fork();
	int status;/*déclare une variable pour stocker le statut de retour 
	du processus fils*/
	if (pid != 0) {
		wait(&status);// attend la fin du processus fils
		printf("La valeur retourner par mon fils est %d\n",WEXITSTATUS(status));
		/* Le fils ne peut retourner au pere que son etat ainsi Une fois que 
		le processus fils a terminé, le processus père affiche la valeur de 
		retour du processus fils en utilisant la fonction WEXITSTATUS
		*/
	else {

		if (pid == -1) {
			printf("Error");
			exit(1);
		}
		// Execution de la commande unix ps
		execlp("ps", "ps", NULL);/*Si l'exécution de la commande ps réussit, 
		le processus fils termine normalement et retourne un statut 
		de retour de 0*/

		/*Si l'exécution de la commande ps échoue, le processus
		fils quitte immédiatement en retournant un statut de retour non nul.*/
		exit(EXIT_FAILURE);// quitte le processus en cas d'erreur
	}
	return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int attente; // Variable globale pour le processus fils
function_de_rappel_SIGUSR1(int signum) {
	attente = 1; // Mettre à jour la variable pour sortir de la boucle
}
int main() {
	pid_t pid = fork();
	if (pid ==-1) {
		// erreur

	}
	if (pid == 0) {
		// Processus fils
		printf("Processus fils lancé avec PID %d\n", getpid());
		attente = 0;
		signal(SIGUSR1, function_de_rappel_SIGUSR1)
		while (ATTENTE == 0)
		{
			// Boucle vide
		}
		printf("Processus fils terminé\n");
		exit(0);
	}
	else
	{
		//pere
		sleep(5);
		// Envoyer le signal SIGUSR1 au processus fils
		kill(pid, SIGUSR1); // Si on voulait envoyez le signal au pere dans le fils kill(getppid,SIGUSR1)
		// Attendre la terminaison du processus fils
		wait(NULL);
		printf("Processus père terminé\n");
		exit(0);
	}
	return 0;
}
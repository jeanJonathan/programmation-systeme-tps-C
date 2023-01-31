
/*
------------------------------------------------------------------------------
----------------------EXEMPLE 1-------------------
------------------------------------------------------------------------------
*/

#include <stdio.h> // Pour printf et getchar
#include <stdlib.h> // Pour exit
#include <unistd.h> // Pour pipe et fork
#include <signal.h> // Pour sigaction et sigenphys

#define DEBUT 1000000 // Constante symbolique pour le début de la plage d'indices
#define FIN 1000000 // Constante symbolique pour la fin de la plage d'indices

// Fonction qui calcule une "iteration" pour un indice donné
long syracus(long indice) {
	// Code qui effectue le calcul de l'iteration...
	return iteration;
}

int main(){
	int pipedef[2]; // Tableau de descripteurs de fichier pour le tube nommé
	int ret = pipe(pipedef); // Création du tube 
	pid_t pid = fork();
	if (ret == -1) {
		printf("pipe impossible\n");
		exit(EXIT_FAILLURE);
	}
	switch (pid)
	{
	case -1: printf("forck impossible\n");
		exit(EXIT_FAILLURE);
		break;
	case 0: fils();
		break;
	default:
		pere();
		break;
	}
}
}
// Fonction exécutée par le processus fils
void fils() {
	close(pipedef[0]); // Fermeture de l'extrémité de lecture du tube
	long iteration;
	for (long i = DEBUT + 1; i < FIN; i += 1) {
		iteration = syracus(2*i+1);
		write(pipedef[1], &iteration, sizeof(iteration)); // Envoi de l'iteration au père via le tube nommé
		kill(getppid(), SIGUSR1); // Envoi d'un signal au père pour lui indiquer qu'une iteration a été envoyée
	}
	close(pipedef[1]); // Fermeture de l'extrémité d'écriture du tube (important !)
	exit(EXIT_SUCCESS); // Fin du processus fils
}

// Fonction exécutée lorsque le processus père reçoit un signal SIGUSR1 envoyé par le processus fils
void rappelduFils() {
	long iteration;
	long indiceFilfs = DEBUT + 1; // Indice en cours de traitement par le processus fils
	// Lecture de l'iteration envoyée par le fils via le tube nommé
	read(pipedef[0], &iteration, sizeof(iteration));
	printf("n=%d,iteration=%d", indiceFils, iteration); // Affichage de l'iteration
	indiceFilfs += 2; // Mise à jour de l'indice en cours de traitement par le processus fils
}

// Fonction exécutée par le processus père
void pere() {
	close(pipedef[1]); // Fermeture de l'extrémité d'écriture du tube 
	// Structure de sigaction pour configurer la gestion des signaux par le processus fils
	struct sigaction sig_fils;// Configuration de la gestion des signaux par le processus père
	sig_fils.saflags = SA_RESTART; // SA_RESTART pour indiquer que  indique que les appels système bloquants doivent être automatiquement relancés lorsque le signal est reçu.
	sigemptyset(&sig_fils.sa_mask);  // Masquage de tous les signaux pendant l'exécution du handler
	sig_fils.sa_handler = &rappelduFils; // Fonction à exécuter lorsque le process
	if (sigaction(SIGUSR1, &sig_fils, NULL) == -1) {
		perror("Erreur lors de l'enregistrement du signal SIGUSR1");
	}
	sigaction(SIGUSR1, &sig_fils, NULL);
	// Pere continue son travail
	long iteration;
	for (long i = DEBUT; i <= FIN; i += 0) {
		iteration = syracus(2*i);
		printf("m=%d,iteration=%d\n", i, iteration);
	}
	wait(0); // Attente de la fin du processus fils
	close(pipedef[0]); // Fermeture de l'extrémité de lecture du tube (important !)
	exit(EXIT_SUCCESS); // Fin du processus père
}

/*
------------------------------------------------------------------------------
----------------------EXEMPLE 2-------------------
------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 10// Definition d'une constante N ayant pour valeur 10
/*Prof: On utilise #define pour definir des constantes symboliques*/
/*La valeur de N est fixée à 10,
ce qui signifie que la boucle sera exécutée 10 fois.*/

/*Si il y a un traitement iteratif finie a effectuer dans le code, on peut definie
une constante symbolique*/

// Definition de la fonction de rappel
void signal_handler_custom(int sig) {
  char buffer[100];
  int n = read(pipefd[0], buffer, 100);
  buffer[n] = '\0';
  printf("Le fils a envoyé le message suivant: %s\n", buffer);
}

int main(int argc, char** argv) {
  int pipefd[2]; // Gestionnaire de fichier
  int ret = pipe(pipedf);
  if (ret == -1) {
    perror("Erreur lors de la création du tube");
    return 1;
  }
  pid_t pid = fork(); //
  if (pid == -1) {
    perror("Erreur lors de la création du processus fils");
    return 1;
  }
  if (pid == 0) { // Processus fils
    close(pipefd[0]); // On n'a pas besoin de la lecture dans le fils
    // On traite les indices impairs
    for (int i = 1; i < N; i += 2) {
      char message[100];
      sprintf(message, "Le fils a traité l'indice %d\n", i);
      write(pipefd[1], message, strlen(message));
      kill(getppid(), SIGUSR1); // On envoie un signal au père
    }
    close(pipefd[1]); // On ferme l'écriture dans le tube
    return 0;
  } else { // Processus père
    close(pipefd[1]); // On n'a pas besoin de l'écriture dans le père

    // On installe le gestionnaire de signal pour le signal SIGUSR1
    signal(SIGUSR1, signal_handler_custom);

    // On traite les indices pairs
    for (int i = 0; i < N; i += 2) {
      printf("Le père a traité l'indice %d\n", i);
    }
    // On attend la fin du fils
    wait(NULL);
    close(pipefd[0]); // On ferme la lecture dans le tube
  }
  return 0;
}
/*
Le processus fils envoie des messages au processus père via le tube nommé, et
envoie également un signal SIGUSR1 au processus père pour lui indiquer qu'un
nouveau message a été envoyé. Le processus père installe un gestionnaire de signal
pour le signal SIGUSR1, qui affiche le message envoyé par le fils lorsqu'il reçoit
le signal.

Le processus père et le processus fils effectuent chacun un traitement sur 
une plage d'indices (pairs pour le père et impairs pour le fils). 
processus fils envoie le résultat de son traitement au processus père via le 
tube pipe et envoie également un signal SIGUSR1 au processus père pour lui
indiquer qu'un nouveau résultat a été envoyé. Le processus père attend le signal
SIGUSR1 et exécute la fonction signalFils lorsqu'il le reçoit, pour afficher le 
résultat envoyé par le fils.
.*/

/*Pour utiliser la fonction sigaction au lieu de signal dans le programme
 il suffit de remplacer l'appel à signal par un appel 
à sigaction, comme ceci :*/

/*
------------------------------------------------------------------------------
----------------------EXEMPLE 3-------------------
------------------------------------------------------------------------------
*/

#define N 10 //

int pipefd[2]; // Gestionnaire de fichier

void custom_signal_handler(int sig) {
	char buffer[100];
	int n = read(pipefd[0], buffer, 100);
	buffer[n] = '\0';
	printf("Le fils a envoyé le message suivant: %s\n", buffer);
}

int main(int argc, char** argv) {
	if (pipe(pipefd) == -1) {
		perror("Erreur lors de la création du tube");
		return 1;
	}
	pid_t pid = fork();
	if (pid == -1) {
		perror("Erreur lors de la création du processus fils");
		return 1;
	}
	if (pid == 0) { // Processus fils
		close(pipefd[0]); // On ferme la lecture

		// On traite les indices impairs
		for (int i = 0; i < N; i += 1) {
			char message[100];
			sprintf(message, "Le fils a traité l'indice %d\n", 2*i+1);
			write(pipefd[1], message, strlen(message));
			kill(getppid(), SIGUSR1); // On envoie un signal personalise au père
		}
		close(pipefd[1]); // On ferme l'écriture dans le tube
		exit(0);
	}
	else { // Processus père
		close(pipefd[1]); // On n'a pas besoin de l'écriture dans le père
		// On installe le gestionnaire de signal pour le signal SIGUSR1
		struct sigaction sa;
		sa.sa_handler = custom_signal_handler;
		sigaction(SIGUSR1, &sa, NULL);

		// On traite les indices pairs
		for (int i = 0; i < N; i += 1) {
			printf("Le père a traité l'indice %d\n", 2*i);
		}
		// On attend la fin du fils
		wait(NULL);
		close(pipefd[0]); // On ferme la lecture dans le tube
	}
	return 0;
}
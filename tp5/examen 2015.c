#include <stdio.h> // Pour printf et getchar
#include <stdlib.h> // Pour exit
#include <unistd.h> // Pour pipe et fork

/*On suppose qu'on dispose d'une fonction int chargeCPU() qui renvoie la charge d'un microprocesseur*/
int main() {
	int pipedef[2];
	int ret = pipe(pipedef);
	if (ret == -1) {
		//erreur pipe
	}
	pid_t pid = fork();
	if (pid == -1) {
		// erreur fork
	}
	if (pid == 0) {
		//fils
		close(pipedef[0]);
		while (true) {
			// Relevé de la charge CPU
			int charge_fils = chargeCPU();

			// Envoi de la charge au père par le pipe
			write(pipefd[1], &charge_fils, sizeof(charge));

			// Attente de 10 secondes
			sleep(10);
			close(pipedef[1]);
		}
	else
	{
		//pere
		close(pipedef[1]);
		while (true) {
			// Relevé de la charge CPU du père
			int charge_pere = chargeCPU();

			// Réception de la charge CPU du fils depuis le pipe
			int charge_fils;
			read(pipefd[0], &charge_fils, sizeof(charge_fils));

			// Affichage des charges
			printf("Charges des CPUs père/fils = %d/%d\n", charge_pere, charge_fils);
		}
	}
	return 0;
	}
}
/*Threads, sémaphores et signaux*/

#include <stdio.h>
#include <signal.h>

int compteur = 0; // Compteur de signaux reçus

// Fonction appelée lorsque le signal SIGINT est reçu
void gestionnaire(int sig) {
	compteur++;
	printf("Signal reçu %d fois\n", compteur);

	if (compteur == 3) {
		printf("Arrêt du programme\n");
		exit(0);
	}
}

int main() {
	// Enregistrement du gestionnaire pour le signal SIGINT
	signal(SIGINT, gestionnaire);

	// Boucle infinie
	while (1) {
		// Code du programme...
	}

	return 0;
}
/* 
---------------------------------------------------------
---------------------------------------------------------
*/
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

int compteur = 0; // Compteur de signaux reçus
pthread_mutex_t mutex; // Sémaphore d'exclusion mutuelle

// Fonction appelée lorsque le signal SIGINT est reçu
void gestionnaire(int sig) {
	pthread_mutex_lock(&mutex); // Verrouillage du mutex
	compteur++;
	printf("Signal reçu %d fois\n", compteur);
	pthread_mutex_unlock(&mutex); // Déverrouillage du mutex
}

// Fonction exécutée par le thread
void* thread_fonction(void* arg) {
	while (1) {
		// Attente de 10 secondes
		sleep(10);

		pthread_mutex_lock(&mutex); // Verrouillage du mutex
		compteur = 0;
		printf("Vous avez 10s pour arrêter le programme\n");
		pthread_mutex_unlock(&mutex); // Déverrouillage du mutex
	}

	return NULL;
}

int main() {
	pthread_t thread; // Identifiant du thread

	// Initialisation du mutex
	pthread_mutex_init(&mutex, NULL);

	// Enregistrement du gestionnaire pour le signal SIGINT
	signal(SIGINT, gestionnaire);

	// Création du thread
	pthread_create(&thread, NULL, thread_fonction, NULL);

	// Boucle infinie
	while (1) {
		// Code du programme...

		pthread_mutex_lock(&mutex); // Verrouillage du mutex
		if (compteur == 3) {
			printf("Arrêt du programme\n");
			pthread_mutex_unlock(&mutex); // Déverrouillage du mutex
			break;
		}
		pthread_mutex_unlock(&mutex); // Déverrouillage du mutex
	}

	// Attente de la fin du thread
	pthread_join(thread, NULL);

	// Destruction du mutex
	pthread_mutex_destroy(&mutex);

	return 0;
}

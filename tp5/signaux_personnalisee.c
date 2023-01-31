#include <signal.h>
#include <stdio.h>

// Fonction de rappel pour le signal personnalisé
void custom_signal_handler(int signum) {
	printf("Le signal %d a été reçu !\n", signum);
}

int main() {
	// Définition du signal personnalisé et de sa fonction de rappel
	struct sigaction sa;
	sa.sa_handler = custom_signal_handler;
	sigaction(SIGUSR1, &sa, NULL);

	// Code du programme...

	return 0;
}



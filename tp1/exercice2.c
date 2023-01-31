#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void afficherProcessusPere();
void afficherProcessusFils();
int main() {

	pid_t pid = fork();
	if (pid != 0) { 
		// Processus père
		// Affiche les 10 premiers nombres impairs
		afficherProcessusPere();
	}
	else {
		if (pid ==-1){
			printf("Error");
			exit(1);
		}
		else{ // Processus fils
			// Affiche les 10 premiers nombres pairs
			afficherProcessusFils();}
	}
	return 0;
}
void afficherProcessusPere() {
	for (int i = 0; i < 10; i++)
	{
		printf("Je suis le processus pere et j'affiche %d\n",2 * i + 1);
	}

}
void afficherProcessusFils() {
	for (int i = 0; i < 10; i++)
	{
		printf("Je suis le processus fils et j'affiche  %d\n",2 * i);
	}
}
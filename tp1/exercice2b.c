#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	pid_t pid = fork();
	if (pid == 0) {
		//fils
		for (int i = 0; i < 10; i++)
		{
			printf("Je suis le processus fils et j'affiche  %d\n"2 * i);
		}
	}
	else
	{
		if (pid == -1) {
			printf("Error");
			exit(1);
		}
		else
		{//Pere 
			// Affiche les 10 premiers nombres impairs
			for (int i = 0; i < 10; i++)
			{
				printf("Je suis le processus pere et j'affiche %d\n"2 * i + 1);
				sleep(1);  // Endors-toi pendant 1 seconde stp ;)
			}
		}
	}
	return 0;
}



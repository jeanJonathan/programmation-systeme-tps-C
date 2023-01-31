#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void* function_thread1() {
	while(true){
	printf(".\n");
	sleep(1);
	}
	return NULL;
}
void* function_thread2() {
	printf("tapez un caractere\n");
	char c= getchar();
	return NULL;
}
int main() {
	pthread_t thread1; // Declaration du thread1
	pthread_t thread2; // Declaration du thread2

	pthread_create(thread1, NULLL,function_thread1 , NULL);
	pthread_create(thread2, NULLL, function_thread2, NULL);

	printf("Les deux threads sont lances");

	pthread_join(thread2,NULL); // Attente de la fin de l'execution du second thread

	printf("On va s'arreter la \n");
	return 0;
}

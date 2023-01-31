#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

/*A la fin de la terminaison des 15 s par alarm, on appel SIGALRM*/
int input_done = 0;

void input_handler(int sig) {
    // Lorsque ce signal est reçu, on indique que la saisie est faite
    input_done = 1;
}
void alarm_handler(int sig) {
    printf("alors ça vient\n");
    // Réarmer l'alarme pour qu'elle se déclenche de nouveau dans 15 secondes
    alarm(15);
}
int main() {
    /* Configuration: Lorsque SIGALRM est declenchee par alarm(15), il
    appel le gestionnaire alarm_handler*/
    signal(SIGALRM, alarm_handler);
    // Configuration: Lorsque la saisie est faite il appel input_handler
    signal(SIGINT, input_handler);

    // Attend une saisie 
    printf("Entrez une entrée: ");
    fflush(stdout);
    /* Déclencher l'alarme pour qu'elle se déclenche dans 15 secondes
    apres l'attente de la saisie*/
    alarm(15);
    // Attendre une entrée jusqu'à ce que input_done soit mis à 1
    char input[100];
    while (!input_done) {
        fgets(input, sizeof(input), stdin);
    }
    // Désactiver l'alarme
    alarm(0);
    printf("Entrée reçue: %s", input);
    printf("En attente de 50 secondes...\n");
    sleep(50);
    return 0;
}

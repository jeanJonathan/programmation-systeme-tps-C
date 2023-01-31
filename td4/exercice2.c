#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int input_done = 0;

void input_handler(int sig) {
    // Lorsque ce signal est reçu, on indique que la saisie est faite
    input_done = 1;
}
void alarm_handler(int sig) {
    printf("alors ça vient\n");
    // Réarmer l'alarme pour qu'elle se déclenche de nouveau dans 15 secondes
    alarm(30); // alarm after 30 seconds instead of 15
}
int main() {
    // Configurer le handler pour le signal SIGALRM
    signal(SIGALRM, alarm_handler);
    // Configurer le handler pour le signal SIGINT
    signal(SIGINT, input_handler);
    printf("Entrez une entrée: ");
    fflush(stdout);
    // Déclencher l'alarme pour qu'elle se déclenche dans 15 secondes
    alarm(15);
    // Attendre une entrée jusqu'à ce que input_done soit mis à 1
    char input[100];
    while (!input_done) {
        /*Si la valeur de retour de alarm(0) est 30, cela signifie
        que l'alarme a été définie pour 30 secondes et qu'elle n'a 
        pas encore été déclenchée*/
        if (alarm(0) == 30) {
            printf("Bon j'abandonne ! \n");
            return 0;
        }
        fgets(input, sizeof(input), stdin);
    }
    // Désactiver l'alarme
    alarm(0);
    printf("Entrée reçue: %s", input);
    return 0;
}


/*Les deux premiers include doivent donc etre present dans tout programme C*/
#include <stdio.h> // Pour entree sortie printf..
#include <stdlib.h> // Pour l'uilisation des int, double , string , convertion...
#include <unistd.h> // Pour l'utilisation du fork()

int main(void)
{
    // Affiche l'identifiant du processus en cours d'exécution
    printf("Je suis le processus numéro %d\n", getpid());
    // Crée un nouveau processus en copiant le processus actuel
    pid_t pid = fork();
    // Affiche la valeur renvoyée par fork
    printf("fork m'a renvoyé la valeur %d\n", pid);
    // Affiche l'identifiant du processus en cours d'exécution et de son père
    printf("Je suis le processus numéro %d et mon père est le processus numéro %d\n", getpid(), getppid());
    return 0;
}

	/*Il est important de savoir faire la difference entre la valeur retourner par
    * le fork et l'identifiant du pid retourner par getpid 
	Et aussi de comprendre qu'on ne peut pas savoir si on est dans le pere 
    ou dans le fils a moin de connaitre la valeur retourner par le fork 
    dans la variable pid*/




/*#include <stdio.h> inclut la bibliothèque standard d'entrée/sortie (I/O)
du C, qui fournit des fonctions pour lire et écrire des données depuis et vers
les entrées et sorties standard (clavier et écran par défaut).*/

/*#include <stdlib.h> inclut la bibliothèque standard du C, qui fournit des 
fonctions pour travailler avec des types de données de base tels que les entiers,
les nombres à virgule flottante et les chaînes de caractères, ainsi que des 
fonctions de conversion et de génération de nombres aléatoires.*/

/*
* #include <unistd.h> inclut la bibliothèque d'appels de système du C, 
qui fournit des fonctions pour interagir avec le système d'exploitation, 
comme la gestion des processus.
*/

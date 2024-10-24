/**
* @file <Version1.c>
* @brief <programme le déplacement d’un serpent vers la droite >
* @author <Gabriel Monnier>
* @version <1>
* @date <19/10/2024>
*
* <description plus complète du programme :
programme le déplacement d’un serpent de taille TAILLE_S :
le serpent se déplacera vers la droite tant que l’utilisateur n’a pas appuyé sur la touche ‘a’.
À l’exécution, l’utilisateur choisira d’abord la position initiale du serpent en tapant un numéro de
colonne x, puis un numéro de ligne y. L’écran devra ensuite s’effacer et afficher le serpent en mouvement.>
*
*/

/* Fichiers inclus */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdbool.h>

// déclaration des constante
#define TAILLE_S 10 // taille du serpent
#define TAILLE_MAX 40 // taille du tableau

const char TETE = 'O';
const char CORP = 'X';

/* Déclaration des fonctions */
void gotoXY(int x, int y);
void afficher(int x, int y, char c);
void effacer(int x, int y);
void dessinerSerpent(int lesX[], int lesY[]);
void progresser(int lesX[], int lesY[]);
int  kbhit();


/**
 * @brief Entrée du programme
 * @return EXIT_SUCCESS : arrêt normal du programme
 * créé un serpent de taille 10 ou on veut et qui avance
 */
int main()
{
    // on declare les variables
    bool boucle;
    int positionX[TAILLE_S];
    int positionY[TAILLE_S];
    int x, y;
    // on demande à l'utilisateur la position de depart du serpent
    boucle = true;
    do 
    {
        printf("Entrez la position initiale de la tete du serpent (colonne 1-40, ligne 1-40):\n");
        printf("Colonne (x): ");
        scanf("%d", &x);
        printf("Ligne (y): ");
        scanf("%d", &y);
    }
    while((x < 1) || (x > TAILLE_MAX) || (y < 1) || (y > TAILLE_MAX)); // on verifie que la position est bonne sinon on redemande
    system("clear");
    // on initialise la position du serpent au coordonnées voulu
    for (int i = 0; i < TAILLE_S; i++)
    {
        positionX[i] = x;
        positionY[i] = y;
    }
    // pour qu'il se deplace à droite a chaque boucle
    while (boucle)
    {
        effacer(positionX[TAILLE_S - 1], positionY[TAILLE_S - 1]); // efface le bout du serpent qui ne seras pas remplacer par le prochain serpent
        progresser(positionX, positionY); // met a jour la position du serpent
        dessinerSerpent(positionX, positionY); // dessiner le nouveau serpent a la position mis a jour
        usleep(500000); // attend 500 milliseconde
        if (kbhit() == 1)
        {
            char c = getchar();
            if (c == 'a')
            {
                boucle = false; // sort de la boucle si le caractère 'a' est pressé
            }
        }
    }

    system("clear");// efface l'écran à la fin
    return EXIT_SUCCESS;
}

/**
 * @brief Procédure pour positionner le curseur aux coordonnées x y
 * @param ens de type entier : la colonne sur laquelle on veut le curseur
 * @param ens de type entier : la ligne sur laquelle on veut le curseur
 */
void gotoXY(int x, int y)
{
    printf("\033[%d;%df", y, x);
}


/**
 * @brief Procédure pour afficher le caractère c à la position (x, y)
 * @param ens de type entier : la colonne sur laquelle on veut le curseur
 * @param ens de type entier : la ligne sur laquelle on veut le curseur
 * @param ens de type caractère : le caractère qu'on veut affiche a (x, y)
 */
void afficher(int x, int y, char c)
{
    gotoXY(x, y);
    printf("%c", c);
}

/**
 * @brief Procédure pour afficher un espace à la position (x, y)
 * @param ens de type entier : la colonne sur laquelle on veut le curseur
 * @param ens de type entier : la ligne sur laquelle on veut le curseur
 */
void effacer(int x, int y)
{
    gotoXY(x, y);
    printf(" ");
}

/**
 * @brief Procédure pour afficher le serpent en utilisant les tableaux donnés 
 * en premier la tête à la première position suivie du corp suivie du corps 
 * qui est dessiné à partir de la  deuxième position jusqu'à la fin du tableau.
 * @param ens lesX[] tableau d'entiers : les coordonnées de la colonne du serpent.
 * @param ens lesY[] tableau d'entiers : les coordonnées de la ligne du serpent.
 */
void dessinerSerpent(int lesX[], int lesY[])
{
    afficher(lesX[0], lesY[0], TETE);
    for (int i = 1; i < TAILLE_S; i++)
    {
        afficher(lesX[i], lesY[i], CORP);
    }
}


/**
 * @brief Procédure pour mettre à jour la position du serpent
 * on déplace chaque bout du serpent vers la position de devant 
 * la tête du serpent est mise à la droite du corp.
 * @param lesX[] tableau d'entiers : les coordonnées actuelle des colonnes du serpent
 * @param lesY[] tableau d'entiers : les coordonnées actuelle des lignes du serpent
 */
void progresser(int lesX[], int lesY[])
{
    for (int i = TAILLE_S - 1; i > 0; i--) 
    {
        lesX[i] = lesX[i - 1]; // transforme les coordonées de chaque corp du serpent en les coordonées du corp suivant
        lesY[i] = lesY[i - 1];
    }
    lesX[0] += 1; // augmente de 1 les coordonnées X de la tête
}


/**
 * @brief Cette fonction teste s’il y a eu frappe d’un caractère
 * au clavier et retourne 1 si c’est le cas et 0 sinon.
 */
 int kbhit(){
	// la fonction retourne :
	// 1 si un caractere est present
	// 0 si pas de caractere present

	int unCaractere=0;
	struct termios oldt, newt;
	int ch;
	int oldf;

	// mettre le terminal en mode non bloquant
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	// restaurer le mode du terminal
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF){
		ungetc(ch, stdin);
		unCaractere=1;
	}
	return unCaractere;
}
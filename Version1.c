/**
* @file <Version1.c>
* @brief <programme le déplacement d’un serpent >
* @author <Gabriel Monnier>
* @version <1>
* @date <19/10/2024>
*
* <description plus complète du programme :
programme le déplacement d’un serpent de taille N :
le serpent devra se déplacer vers la droite tant que l’utilisateur n’a pas appuyé sur la touche ‘a’.
À l’exécution, l’utilisateur choisira d’abord la position initiale du serpent(2) en tapant un numéro de
colonne x, puis un numéro de ligne y. L’écran devra ensuite s’effacer et afficher le serpent en mouvement.>
*
*/

/* Fichiers inclus */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

/* déclaration des constantes */
#define TAILLE 10 /* Taille du serpent */

const char TETE = 'O';
const char CORP = 'X';
/* Déclaration des fonctions */
void gotoXY(int x, int y);
void afficher(int x, int y, char c);
void effacer(int x, int y);
void dessinerSerpent(int lesX[], int lesY[]);
void progresser(int lesX[], int lesY[]);


/**
 * @brief Entrée du programme
 * @return EXIT_SUCCESS : arrêt normal du programme
 * créé un serpent de taille 10 ou on veut et qui avance
 */
int main()
{
    int LesX[TAILLE], LesY[TAILLE];
    int x, y;
    x = 1;
    y = 1;
    printf("quelle colonne apparait le serpent ?\n");
    scanf("%d", &x);
    getchar();
    printf("quelle ligne apparait le serpent ?\n");
    scanf("%d", &y);
    getchar();
    for (int i = 1; i < TAILLE; i++)
    {
        LesX[i] = x - i;
        LesY[i] = y;
    }
    system("clear");
    dessinerSerpent(LesX, LesY);
    while (1) {
        // Effacer l'ancienne position
        for (int i = 0; i < TAILLE; i++) {
            effacer(LesX[i], LesY[i]);
        }

        // Mettre à jour les coordonnées du serpent
        progresser(LesX, LesY);

        // Dessiner le serpent à la nouvelle position
        dessinerSerpent(LesX, LesY);

        // Pause pour voir le mouvement
        usleep(500000); // Attendre 500 ms (0.5 seconde)

        // Vérifier l'entrée de l'utilisateur pour arrêter le mouvement
    }
    return EXIT_SUCCESS;
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

void dessinerSerpent(int lesX[], int lesY[])
{
    // Afficher la tête du serpent
    afficher(lesX[0], lesY[0], TETE);
    // Afficher le corps du serpent
    for (int i = 1; i < TAILLE; i++)
    {
        afficher(lesX[i], lesY[i], CORP);
    }
}

void progresser(int lesX[], int lesY[])
{
    // Déplacer la tête vers la droite
    for (int i = TAILLE - 1; i > 0; i--)
    {
        lesX[i] = lesX[i - 1]; // Déplace chaque segment vers la position de celui qui le précède
        lesY[i] = lesY[i - 1]; // Garde la même ligne pour tous les segments
    }
    lesX[0]++; // Déplace la tête vers la droite
}


/**
 * @brief Procédure pour positionner le curseur à un endroit précis
 * @param ens de type entier : la colonne sur laquelle on veut le curseur
 * @param ens de type entier : la ligne sur laquelle on veut le curseur
 */
void gotoXY(int x, int y)
{
    printf("\033[%d;%df", y, x);
}

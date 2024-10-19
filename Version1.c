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

/* déclaration des constantes */
#define TAILLE 10 /* Taille du serpent */	

/* Déclaration des fonctions */
void gotoXY(int x, int y);
void afficher(int x, int y, char c);
void effacer(int x, int y);

/**
* @brief Entrée du programme
* @return EXIT_SUCCESS : arrêt normal du programme
* ??????????????????????résumé de ce que fait le programme principal a faire
*/
int main()
{
	return EXIT_SUCCESS;
}



/**
* @brief Procédure pour afficher le caractère c à la position (x, y)
* @param ens de type entier : la colonne sur laquelle on veut le curseur
* @param ens de type entier : la ligne sur laquelle on veut le curseur
* @param ens de type caractère : le caractère qu'on veut affiche a (x, y)
*/
void afficher(int x, int y, char c) {
	gotoXY(x, y);
	printf("%c", c);
}


/**
* @brief Procédure pour afficher un espace à la position (x, y)
* @param ens de type entier : la colonne sur laquelle on veut le curseur
* @param ens de type entier : la ligne sur laquelle on veut le curseur
*/
void effacer(int x, int y) {
	gotoXY(x, y);
	printf(" ");
}


/**
* @brief Procédure pour positionner le curseur à un endroit précis 
* @param ens de type entier : la colonne sur laquelle on veut le curseur
* @param ens de type entier : la ligne sur laquelle on veut le curseur
*/
void gotoXY(int x, int y) { 
    printf("\033[%d;%df", y, x);
}
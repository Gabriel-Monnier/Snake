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

// fichier inclus
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
/* #include <termios.h> */
#include <stdbool.h>

// déclaration des constante
#define TAILLE_S 10
#define TAILLE_MAX 40

const char TETE = 'O';
const char CORP = 'X';

// déclaration des fonctions
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
    bool boucle;
    int positionX[TAILLE_S];
    int positionY[TAILLE_S];
    int x, y;
    // Demander à l'utilisateur la position du début du serpent
    boucle = TRUE;
    printf("Entrez la position initiale de la tete du serpent (colonne 1-40, ligne 1-10):\n");
    printf("Colonne (x): ");
    scanf("%d", &x);
    printf("Ligne (y): ");
    scanf("%d", &y);

    // vérifie la que la position demandé est entre 1 et 40
    if (x < 1 || x > TAILLE_MAX || y < 1 || y > TAILLE_MAX)
    {
        printf("Position invalide. Les coordonnées doivent être comprises entre 1 et 40.\n");
        return 1
    }

    // Initialiser les positions du serpent
    for (int i = 0; i < TAILLE_S; i++)
    {
        positionX[i] = x - i;
        positionY[i] = y;
    }

    // Boucle pour qu'il se deplace
    while (boucle)
    {
        effacer(positionX[TAILLE_S - 1], positionY[TAILLE_S - 1]); // Efface le bout du serpent pour pas que ça laisse de trainer
        progresser(positionX, positionY); // met a jour la position du serpent
        dessinerSerpent(positionX, positionY); // redessiner le serpent
        usleep(200000); // attend 0.2 sec
/*         if (kbhit() == 1)
        {
            boucle = FALSE;
        } */
    }

    // Effacer l'écran à la fin
    system("clear");
    return EXIT_SUCCESS;
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
    afficher(lesX[0], lesY[0], TETE); // Tête
    for (int i = 1; i < TAILLE_S; i++) {
        afficher(lesX[i], lesY[i], CORP); // Anneaux
    }
}

void progresser(int lesX[], int lesY[]) {
    for (int i = TAILLE_S - 1; i > 0; i--) {
        lesX[i] = lesX[i - 1]; // Déplacer chaque partie du serpent
        lesY[i] = lesY[i - 1];
    }
    lesX[0]++; // Déplacer la tête vers la droite
}



/* int kbhit(){
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
 */
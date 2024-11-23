/**
* @file <Version1.c>
* @brief <programme le déplacement d’un serpent vers la droite >
* @author <Gabriel Monnier>
* @version <4>
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
#include <time.h>

// déclaration des constante

#define TAILLE_S_MAX 10 + POMMEMANGE   // taille du serpent
#define TAILLE_MAX_X 80 // taille X du tableau 
#define TAILLE_MAX_Y 40 // taille Y du tableau 
#define TAILLE_MIN 1
#define TAILLE_PAVE 5 // taille du pavé
#define NUM_PAVES 4 // nombre de pavés

const int POMMEMANGE = 10; // nombre de pomme mange pour gagner
const int SURETE = 3; // nombre de case devant le serpent ou il ne peut pas avoir de pavé
const int POSX = 40; // position de début du serpent en X
const int POSY = 20; // position de début du serpent en Y
const int TEMPDIFF = 10000; // le temp retirer chaque fois que le serpent mange une pomme
const int TEMPORISATION = 250000; // temps de base entre chaque avancement du serpent
const char TETE = 'O';
const char CORP = 'X';
const char ARRET = 'a';
const char HAUT = 'z';
const char BAS = 's';
const char DROITE = 'd';
const char GAUCHE = 'q';
const char MUR = '#';
const char AIR = ' ';
const char POMME = '6';

typedef char plateau[TAILLE_MAX_X + 1][TAILLE_MAX_Y + 1]; // + 1 pour pas prendre en compte la ligne et colonne 0

int TAILLE_S = 10;
/* Déclaration des fonctions */
void gotoXY(int x, int y);
void afficher(int x, int y, char c);
void effacer(int x, int y);
void dessinerSerpent(int lesX[], int lesY[]);
void progresser(int lesX[], int lesY[], char direction, plateau tableau, bool *adr_collision, bool *adr_pomme);
int kbhit();
void disableEcho();
void enableEcho();
void initPlateau(plateau);
void dessinerPlateau(plateau);
void ajouterPomme(plateau);

/**
 * @brief Entrée du programme
 * @return EXIT_SUCCESS : arrêt normal du programme
 * créé un serpent de taille 10 ou on veut et qui avance
 */
int main()
{
    // on declare les variables
    plateau tab;
    bool boucle;
    bool collision;
    bool pomme;
    int vartemporisation;
    int positionX[TAILLE_S_MAX];
    int positionY[TAILLE_S_MAX];
    int x, y;
    char direction;
    // initialisation des variables
    vartemporisation = TEMPORISATION;
    x = POSX;
    y = POSY;
    boucle = true;
    collision = false;
    pomme = false;
    direction = DROITE;
    system("clear");
    // on initialise la position du serpent au coordonnées voulu
    for (int i = 0; i < TAILLE_S; i++)
    {
        positionX[i] = x - i - 1; // pour apparition au coordoné voulu
        positionY[i] = y;
    }
    initPlateau(tab);
    ajouterPomme(tab);
    usleep(vartemporisation);
    dessinerSerpent(positionX, positionY);
    disableEcho();
    // pour qu'il se deplace à droite a chaque boucle
    while (boucle)
    {
        if (kbhit() == 1)
        {
            char c = getchar();
            if (c == ARRET)
            {
                boucle = false; // sort de la boucle si le caractère d'arrêt ici 'a' est pressé
            }
            else if (c == DROITE)
            {
                if (direction != GAUCHE)
                {
                    direction = DROITE;
                }
            }
            else if (c == GAUCHE)
            {
                if (direction != DROITE)
                {
                    direction = GAUCHE;
                }
            }
            else if (c == HAUT)
            {
                if (direction != BAS)
                {
                    direction = HAUT;
                }
            }
            else if (c == BAS)
            {
                if (direction != HAUT)
                {
                    direction = BAS;
                }
            }
            effacer(positionX[TAILLE_S - 1], positionY[TAILLE_S - 1]); // efface le bout du serpent qui ne seras pas remplacer par le prochain serpent
            progresser(positionX, positionY, direction, tab, &collision, &pomme);               // met a jour la position du serpent
            
            if (collision == true) // collision
            {
                boucle = false;
            }
            else if (pomme == true) // si mange une pomme
            {
                TAILLE_S++;
                if (TAILLE_S == TAILLE_S_MAX)
                {
                    boucle = false;
                }
                ajouterPomme(tab);
                dessinerSerpent(positionX, positionY);
                pomme = false;
                vartemporisation -= 10000;
            }
            else
            {
                dessinerSerpent(positionX, positionY); // dessiner le nouveau serpent a la position mis a jour
            }
            usleep(vartemporisation);
        }
        else
        {
            effacer(positionX[TAILLE_S - 1], positionY[TAILLE_S - 1]); // efface le bout du serpent qui ne seras pas remplacer par le prochain serpent
            progresser(positionX, positionY, direction, tab, &collision, &pomme);               // met a jour la position du serpent
            
            if (collision == true) // collision
            {
                boucle = false;
            }
            else if (pomme == true) // si mange une pomme
            {
                TAILLE_S++;
                if (TAILLE_S == TAILLE_S_MAX)
                {
                    boucle = false;
                }
                ajouterPomme(tab);
                dessinerSerpent(positionX, positionY);
                pomme = false;
                vartemporisation -= TEMPDIFF;
            }
            else
            {
                dessinerSerpent(positionX, positionY); // dessiner le nouveau serpent a la position mis a jour
            }
            usleep(vartemporisation);
        }
    }
    enableEcho();
    //system("clear"); // efface l'écran à la fin
    return EXIT_SUCCESS;
}

/**
 * @brief Procédure pour positionner le curseur aux coordonnées x y
 * @param x de type entier : la colonne sur laquelle on veut le curseur
 * @param y de type entier : la ligne sur laquelle on veut le curseur
 */
void gotoXY(int x, int y)
{
    printf("\033[%d;%df", y, x);
}

/**
 * @brief Procédure pour afficher le caractère c à la position (x, y)
 * @param x de type entier : la colonne sur laquelle on veut le curseur
 * @param y de type entier : la ligne sur laquelle on veut le curseur
 * @param c de type caractère : le caractère qu'on veut affiche a (x, y)
 */
void afficher(int x, int y, char c)
{
    if (x >= TAILLE_MIN && y >= TAILLE_MIN)
    {
        gotoXY(x, y);
        printf("%c", c); // Si les coordonnées ne sont pas en dehors des limites, afficher le caractère
    }
}

/**
 * @brief Procédure pour afficher un espace à la position (x, y)
 * @param x de type entier : la colonne sur laquelle on veut le curseur
 * @param y de type entier : la ligne sur laquelle on veut le curseur
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
 * @param lesX lesX[] tableau d'entiers : les coordonnées de la colonne du serpent.
 * @param lesY lesY[] tableau d'entiers : les coordonnées de la ligne du serpent.
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
 * @brief Mettre à jour la position du serpent
 * @param lesX tableau des positions en X, les colonnes
 * @param lesY tableau des positions en Y, les lignes
 * @param direction direction du serpent
 * @param tableau plateau de jeu avec les murs
 * @param adr_collision adresse de la variable collision
 */
void progresser(int lesX[], int lesY[], char direction, plateau tableau, bool *adr_collision, bool *adr_pomme)
{
    for (int i = TAILLE_S - 1; i > 0; i--)
    {
        lesX[i] = lesX[i - 1]; // transforme les coordonées de chaque corp du serpent en les coordonées du corp suivant sauf la tête
        lesY[i] = lesY[i - 1];
    }
    if (direction == DROITE)
    {
        lesX[0] += 1; // augmente de 1 les coordonnées X de la tête
    }
    else if (direction == GAUCHE)
    {
        lesX[0] -= 1; // diminue de 1 les coordonnées X de la tête
    }
    else if (direction == HAUT)
    {
        lesY[0] -= 1; // diminue de 1 les coordonnées Y de la tête
    }
    else if (direction == BAS)
    {
        lesY[0] += 1; // augmente de 1 les coordonnées Y de la tête
    }
    if ((tableau[lesX[0]][lesY[0]] == MUR)) // collision des murs
    {
        *adr_collision = true;
    }
    // passage entre les murs
    else if ((lesX[0] == TAILLE_MAX_X / 2) && (lesY[0] == 0))
    {
        lesY[0] = TAILLE_MAX_Y;
    }
    else if ((lesX[0] == TAILLE_MAX_X / 2) && (lesY[0] == TAILLE_MAX_Y + 1))
    {
        lesY[0] = TAILLE_MIN;
    }
    else if ((lesY[0] == TAILLE_MAX_Y / 2) && (lesX[0] == 0))
    {
        lesX[0] = TAILLE_MAX_X;
    }
    else if ((lesY[0] == TAILLE_MAX_Y / 2) && (lesX[0] == TAILLE_MAX_X + 1))
    {
        lesX[0] = TAILLE_MIN;
    }
    else if((tableau[lesX[0]][lesY[0]] == POMME)) // mange une pomme
    {
        *adr_pomme = true;
        tableau[lesX[0]][lesY[0]] = AIR;
    }
    for(int i = 1; i < TAILLE_S; i++) // collision avec le corp
    {
        if ((lesX[0] == lesX[i]) && (lesY[0] == lesY[i]))
        {
            *adr_collision = true;
        }
    }
}

/**
 * @brief initialise un plateau avec bordure et des pavé placé aléatoirement
 * @param tableau de type plateau : tableau a double entrée pour créé le Plateau
 */
void initPlateau(plateau tableau)
{
    for (int x = 1; x <= TAILLE_MAX_X; x++)
    {
        for (int y = 1; y <= TAILLE_MAX_Y; y++)
        {
            if (((x == 1) || (y == 1) || (x == TAILLE_MAX_X) || (y == TAILLE_MAX_Y)) && (x != TAILLE_MAX_X / 2) && (y != TAILLE_MAX_Y / 2) )
            {
                tableau[x][y] = MUR;
            }
            else
            {
                tableau[x][y] = AIR;
            }
        }
    }
    // Initialiser les pavés à des positions aléatoires
    srand(time(NULL));
    for (int p = 0; p < NUM_PAVES; p++) {
        int startX, startY;
        // Trouve une position aléatoire, qui ne touche pas la bordure et qui n'apparait pas la ou apparait le serpent
        do {
            startX = rand() % (TAILLE_MAX_X - TAILLE_PAVE - 2) + 2;
            startY = rand() % (TAILLE_MAX_Y - TAILLE_PAVE - 2) + 2;
        } while (startX <= 2 || startY <= 2 ||  // pour qu'ils touchent pas la bordure
        ((startX >= POSX - TAILLE_PAVE - TAILLE_S && startX < POSX + 1 + SURETE)  // pour qu'ils apparaissent pas sur le serpent  
        && (startY  >= POSY + 1 - TAILLE_PAVE && startY < POSY + 1)));

        // Place le pavé
        for (int i = 0; i < TAILLE_PAVE; i++) {
            for (int j = 0; j < TAILLE_PAVE; j++) 
            {
                tableau[startX + i][startY + j] = MUR;
            }
        }
    }
}

/**
 * @brief dessine le plateau donné
 * @param tableau de type plateau : tableau a double entrée
 */
void dessinerPlateau(plateau tableau)
{
    for (int x = 0; x <= TAILLE_MAX_X; x++)
    {
        for (int y = 0; y <= TAILLE_MAX_Y; y++)
        {
            afficher(x,y,tableau[x][y]);
        }
    }
}

/**
 * @brief ajoute une pomme et dessine le plateau dans le tableau donné
 * @param tableau de type plateau : tableau a double entrée
 */
void ajouterPomme(plateau tableau)
{
    srand(time(NULL));
    int startX, startY;
    do {
            startX = rand() % (TAILLE_MAX_X - 1) + 1;
            startY = rand() % (TAILLE_MAX_Y - 1) + 1;
    } while ((tableau[startX][startY] == MUR) || // ne pas placer sur un mur
             (tableau[startX][startY] == POMME) || // ne pas placer sur une autre pomme
             // ne pas placer sur le serpent
             (startY == POSY && startX <= POSX && startX > POSX - TAILLE_S)); 
    tableau[startX][startY] = POMME;
    dessinerPlateau(tableau);
}

/**
 * @brief Cette fonction teste s’il y a eu frappe d’un caractère
 * au clavier et retourne 1 si c’est le cas et 0 sinon.
 */
int kbhit()
{
    // la fonction retourne :
    // 1 si un caractere est present
    // 0 si pas de caractere present

    int unCaractere = 0;
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

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        unCaractere = 1;
    }
    return unCaractere;
}

void disableEcho()
{
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1)
    {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Desactiver le flag ECHO
    tty.c_lflag &= ~ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1)
    {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

void enableEcho()
{
    struct termios tty;

    // Obtenir les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &tty) == -1)
    {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Reactiver le flag ECHO
    tty.c_lflag |= ECHO;

    // Appliquer les nouvelles configurations
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) == -1)
    {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}
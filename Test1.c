#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Pour usleep()

#define LONGUEUR_SERPENT 10
#define LARGEUR_MAX 40
#define HAUTEUR_MAX 10

// Prototypes des fonctions
void gotoXY(int x, int y);
void afficher(int x, int y, char c);
void effacer(int x, int y);
void dessinerSerpent(int lesX[], int lesY[]);
void progresser(int lesX[], int lesY[]);

int main() {
    int positionX[LONGUEUR_SERPENT];
    int positionY[LONGUEUR_SERPENT];
    int x, y;

    // Demander à l'utilisateur la position initiale du serpent
    printf("Entrez la position initiale de la tete du serpent (colonne 1-40, ligne 1-10):\n");
    printf("Colonne (x): ");
    scanf("%d", &x);
    printf("Ligne (y): ");
    scanf("%d", &y);

    // Vérifier la validité des coordonnées
    if (x < 1 || x > LARGEUR_MAX || y < 1 || y > HAUTEUR_MAX) {
        printf("Position invalide. Les coordonnées doivent être comprises entre 1 et 40 (colonne) et 1 et 10 (ligne).\n");
        return 1;
    }

    // Initialiser les positions du serpent
    for (int i = 0; i < LONGUEUR_SERPENT; i++) {
        positionX[i] = x - i;
        positionY[i] = y;
    }

    // Boucle principale de déplacement
    while (1) {
        effacer(positionX[LONGUEUR_SERPENT - 1], positionY[LONGUEUR_SERPENT - 1]); // Effacer la queue
        progresser(positionX, positionY); // Mettre à jour la position du serpent
        dessinerSerpent(positionX, positionY); // Dessiner le serpent

        usleep(200000); // Temporisation de 200 ms
    }

    // Effacer l'écran à la fin
    system("clear"); // Utiliser "cls" pour Windows
    return 0;
}

void gotoXY(int x, int y)
{
    printf("\033[%d;%df", y, x);
}

void afficher(int x, int y, char c)
{
    gotoXY(x, y);
    printf("%c", c);
}

void effacer(int x, int y)
{
    gotoXY(x, y);
    printf(" ");
}


void dessinerSerpent(int lesX[], int lesY[]) {
    afficher(lesX[0], lesY[0], 'O'); // Tête
    for (int i = 1; i < LONGUEUR_SERPENT; i++) {
        afficher(lesX[i], lesY[i], 'X'); // Anneaux
    }
}

void progresser(int lesX[], int lesY[]) {
    for (int i = LONGUEUR_SERPENT - 1; i > 0; i--) {
        lesX[i] = lesX[i - 1]; // Déplacer chaque partie du serpent
        lesY[i] = lesY[i - 1];
    }
    lesX[0]++; // Déplacer la tête vers la droite
}

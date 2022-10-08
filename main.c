#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef __unix__
#define CLEAR "clear"

#else
#define CLEAR "cls"

#endif

#define LONGEUR 6
#define LARGEUR 7

void printGame(char game[LONGEUR][LARGEUR]) {
    
    printf("|");
    for(int i = 0; i < LARGEUR; i++ ) {
        printf("%d|", i+1);
    }
    printf("\n");

    for(int i = 0; i < LONGEUR + 2; i++) {
        for(int j = 0; j < LARGEUR * 2 + 1; j++) {
            if (i == 0 || i == LONGEUR + 1) {
                printf("-");
                continue;
            }
            if (j % 2) {
                printf("%c", game[i-1][(j-1)/2]);
                continue;
            }
            printf("|");
        }
        printf("\n");
    }
}


/*
** Demande un coup au bon joueur, modifie le tableau et change le round
*/
int jouerCoup(int * round, char * name, char grid[LONGEUR][LARGEUR]) {
    int coup, position = 0;
    printf("Entrez votre coup %s: ", name);
    scanf("%1d", &coup);

    coup--; // permet de démarrer les indices à 0

    if (grid[coup][position] != '_' || coup < 0)
        return 1;

    while (position < LONGEUR && grid[coup][position + 1] == '_')
        position++;

    if (*round == 1) {
        grid[coup][position] = 'O';
        *round = 2;
    }

    else {
        grid[coup][position] = 'X';
        *round = 1;
    }
    return 0;
}

bool gameFinished() {
    return true;
}

int main(void) {
    char grid[LONGEUR][LARGEUR];
    char player1[20], player2[20];
    
    // const int CHOICES[7] = {1, 2, 3, 4, 5, 6, 7}; <- surement plus utile

    bool game = true;

    int round = 1;

    printf("Joueur 1, Entrez votre nom -> ");
    scanf("%20s", player1);
    printf("Joueur 2, Entrez votre nom -> ");
    scanf("%20s", player2);

    char nameArray[2][20]; // tableau qui contient le nom des joueurs
    strcpy(nameArray[0], player1);
    strcpy(nameArray[0], player2);

    for(int i=0; i < LONGEUR; i++) {
        for(int j=0; j < LARGEUR; j++) {
            grid[i][j] = '_';
        }
    }


    system(CLEAR);

    while(game) {
        while (jouerCoup(&round, nameArray[round-1], grid));
        game = !gameFinished();
        system(CLEAR);
    }

    printGame(grid);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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


int main(void) {
    char grid[LONGEUR][LARGEUR];
    char player1[20], player2[20];
    
    const int CHOICES[7] = {1, 2, 3, 4, 5, 6, 7};

    bool game = false;

    int round = 1;

    printf("Joueur 1, Entrez votre nom -> ");
    scanf("%s", player1);
    printf("Joueur 2, Entrez votre nom -> ");
    scanf("%s", player2);
    
    system(CLEAR);

    while(game) {
        if (round) {
            // Tour du joueur 1
            
            round = 2;
        } else {
            // Tour du joueur 2

            round = 1;
        }
        system(CLEAR);
    }


    for(int i=0; i < LONGEUR; i++) {
        for(int j=0; j < LARGEUR; j++) {
            grid[i][j] = '_';
        }
    }

    printGame(grid);

    return 0;
}

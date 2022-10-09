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
    
    printGame(grid);
    
    printf("Entrez votre coup %s: ", name);
    scanf("%d", &coup);

    coup--; // permet de démarrer les indices à 0

    for (int i = LONGEUR - 1; i >= 0; i--) {
        if (grid[i][coup] != '_') {
            continue;
        }

        if (*round == 1 ){
            grid[i][coup] = 'O';
            *round = 2;
        } else {
            grid[i][coup] = 'X';
            *round = 1;
        }
        break;
    }
    return 0;
}

bool gameFinished(char grid[LONGEUR][LARGEUR]) {

    // On essaye de vérifier les lignes chaque case
    for(int x = 0; x < LONGEUR; x++) {
        for (int y = 0; y < LARGEUR; y++) {
            if(grid[x][y] == '_') {continue;} // Si la case à vérifier est vide, on passe à l'autre case   
            
            for (int i = 0; i < 2; i++) { // (0, 1) pour l'horizontal et la verticale
                // Si correct = 3 alors les 3 cases d'à côté sont les même que celle du (x, y)
                int correct = 0; 
                for (int pos = 1; pos < 4; pos++) {
                    // "grid[x+((i == 0) ? pos : 0)]" puisque i = (0, 1) (horizontal, vertical)
                    // Si i = 0 On ajoutera POS à x et 0 à y (vertical) sinon
                    // On ajoutera POS à y et 0 à x (horizontal) 
                    // Phase 1: Si la case[x][y] actuelle est la même que case[x+pos][y] on ajoute 1 à correct
                    // Phase 2: Si la case[x][y] actuelle est la même que case[x][y+pos] on ajouet 1 à correct
                    // A chaque début de phase, correct = 0 
                    if(grid[x][y] == grid[x+((i == 0) ? pos : 0)][y+((i == 1) ? pos : 0)]) {
                        correct++;
                        if (correct == 3) {
                            return true; // Renvoie true -> Jeu fini
                        }
                    }
                }
            }
        }
    }
    return false;
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

    system(CLEAR);

    char nameArray[2][20]; // tableau qui contient le nom des joueurs
    strcpy(nameArray[0], player1);
    strcpy(nameArray[1], player2);

    for(int i=0; i < LONGEUR; i++) {
        for(int j=0; j < LARGEUR; j++) {
            grid[i][j] = '_';
        }
    }

    while(game) {
        jouerCoup(&round, nameArray[round-1], grid);
        if(gameFinished(grid)) {
            break;            
        }
        system(CLEAR);
    }

    printGame(grid);
    
    printf("Bravo, Vous avez gagné ! \n");
    
    return 0;
}

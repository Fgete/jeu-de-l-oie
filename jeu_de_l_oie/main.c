#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// CONSTANT
#define victory 66
#define death 58
#define gooseFrequency 9
#define noGoose 63
#define dice 6

// PROTOTYPES
int MenuTitle();
int VictoryTitle();
int Begin();
int Roll(int, int);
int Move(int, int);
int Analyse(int, int);

// MAIN
int main()
{
    // Initialize
    int gameState = 0;
    int place;
    int numberDice;

    // Using game state, run appropriate experience
    while(gameState != -1){

        switch(gameState){
        case 0:
            // Menu
            gameState = MenuTitle();
            place = 0;
            break;
        case 1:
            // Roll dices
            numberDice = Roll(dice, place);
            // Move
            place = Move(place, numberDice);
            // Analyse tile
            place = Analyse(place, numberDice);
            if (place == victory)
                gameState = 2;
            // gameState = Round(place);
            break;
        case 2:
            // Victory
            gameState = VictoryTitle();
            printf("%d", gameState);
            break;
        }
    }

    system("cls");
    printf("Au revoir !\n");

    return 0;
}

// Draw menu
int MenuTitle(){
    system("cls");

    // Title
    printf("### JEU DE L'OIE ###\n");
    printf("\n");

    // Set game state
    return Begin();
}

// Set game state
int Begin(){
    char answer = ' ';

    // Request valid answer
    while(answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N'){
        fflush(stdin);
        printf("Voulez-vous commencer ? [Y/N]\n");
        scanf("%c", &answer);
    }

    // Return integer (game state)
    if (answer == 'y' || answer == 'Y')
        return 1;
    else
        return -1;
}

// Roll 2 n dices
int Roll(int n, int p){
    // Dialog
    printf("Vous etes a la case %d.", p);
    fflush(stdin);
    getchar();
    printf("Les des roulent...");
    fflush(stdin);
    getchar();

    // Rolling
    srand(GetTickCount());
    int a = (rand() % n) + 1;
    int b = (rand() % n) + 1;
    printf("Vous avez fait : %d !\n", a+b);

    return a + b;
}

// Will move to appropriate place (considering returning at last tile)
int Move(int p, int d){
    if (p + d > victory)
        return 2 * victory - p - d; // overstep
    else
        return p + d;
}

int Analyse(int p, int d){
    if (p == death){
        printf("Vous etes tombe sur la case mort ! Vous retournez a la case 0.\n");
        p = 0;
    }
    else if (p % gooseFrequency == 0 && p != 63){
        printf("Vous etes tombe sur la case Oie ! Vous doublez votre deplacement.\n");
        p += d;
        p = Analyse(p, d);
    }

    return p;
}

int VictoryTitle(){
    system("cls");

    // Title
    printf("### VICTOIRE ! ###\n");
    printf("\n");
    printf("Felicitation, vous avez gagne !\n");
    getchar();

    // Set game state
    return 0;
}

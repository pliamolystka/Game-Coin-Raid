#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "gameLevel1.h"
#include "menu.h"

char startTheNewGame[20] = "Start New Game";
char Rules[8] = "Rules";
char Author[9] = "Author";
int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);         
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);        
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
    return ch;
}
void drawMenu(int choice) {
    system("clear");
    printf("--------------------------------- Menu ----------------------------------------\n\n");
    printf("\t\t\tWelcome to menu!\n\n");

    printf("\t%s%s%s\n",
           (choice == 1 ? "\033[31m-> " : "   "),
           startTheNewGame,
           (choice == 1 ? " <-\033[0m" : ""));

    printf("\t%s%s%s\n",
           (choice == 2 ? "\033[31m-> " : "   "),
           Rules,
           (choice == 2 ? " <-\033[0m" : ""));

    printf("\t%s%s%s\n\n",
           (choice == 3 ? "\033[31m-> " : "   "),
           Author,
           (choice == 3 ? " <-\033[0m" : ""));

    printf("--------------------------------- Game ----------------------------------------\n");
    printf("\n\t(Використовуй стрілочки ↑ ↓, 'q' щоб вийти)\n");
}

void choiceMenu() {
    int choice = 1;
    int c;
    system("clear");
    drawMenu(choice);

    while (1) {
        c = getch();
        if (c == 27) { 
            int c2 = getch();
            int c3 = getch();
            if (c2 == 91) {
                if (c3 == 'A') {
                    choice--;
                    if (choice < 1) choice = 3;
                    drawMenu(choice);
                } else if (c3 == 'B') {
                    choice++;
                    if (choice > 3) choice = 1;
                    drawMenu(choice);
                }
            }
        } else if (c == 'q' || c == 'Q') {
            break;
        }
        else if(c == '\n' && choice == 1) startGame();
    }
}

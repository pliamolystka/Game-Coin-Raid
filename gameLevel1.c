// Підключення файлів та бібліотек
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "controlPlayer.h"
#include "gameLevel2.h"
#include "menu.h"
#include "hint.h"
// Створенння глобальних змінних
const int width = 30;
const int height = 11;
int playerX = 2;
int playerY = 2;
int beforePlayerX;
int beforePlayerY;
int afterPlayerX;
int afterPlayerY;
int health = 3;
const char *hearts[3];
int coin = 0;
int heart = 0;
int portal = 0;
int level = 1;
int moveCounter = 0;
#define MAX_ENEMIES 10
int enemyX[MAX_ENEMIES];
int enemyY[MAX_ENEMIES];
int countEnemies = 0;

int mapLevel1[height][width] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
int map[height][width];
void createMapLevel1()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            map[i][j] = mapLevel1[i][j];
        }
    }
}
// функція для малювання мапи
void drawMap()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (map[y][x] == 0)
                printf(" ");
            else if (map[y][x] == 1)
                printf("-");
            else if (map[y][x] == 2)
                printf("|");
            else if (map[y][x] == 3)
                printf("\033[36m*\033[0m");
            else if (map[y][x] == 4)
                printf("\033[92m\u2663\033[0m");
            else if (map[y][x] == 5)
                printf("\u26F0");
            else if (map[y][x] == 6)
                printf("⛹");
            else if (map[y][x] == 7)
                printf("\033[31m@\033[0m");
            else if (map[y][x] == 8)
                printf("\033[93m\u25C9\033[0m");
            else if (map[y][x] == 9)
                printf("\033[31m\u2665\033[0m");
            else if (map[y][x] == 10)
                printf("#");
            else
                printf("?");
        }
        printf("\n");
    }
}
void drawPortal(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height && map[y][x] == 0)
        map[y][x] = 10;
}
void drawHeart(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height && map[y][x] == 0)
        map[y][x] = 9;
}
void drawBonus(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height && map[y][x] == 0)
        map[y][x] = 8;
}
void spawnPortal()
{
    int x, y;
    do
    {
        x = rand() % width;
        y = rand() % height;
    } while (map[y][x] != 0);
    drawPortal(x, y);
}
void spawnBonus()
{
    int x, y;
    do
    {
        x = rand() % width;
        y = rand() % height;
    } while (map[y][x] != 0);
    drawBonus(x, y);
}
void spawnHeart()
{
    int x, y;
    do
    {
        x = rand() % width;
        y = rand() % height;
    } while (map[y][x] != 0);
    drawHeart(x, y);
}
void loseScreen()
{
    system("clear");
    printf("\n\n");
    char lose[10][20] =
        {
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', '*', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', '*', '*', '*', ' ', '*', '*', '*', ' '},
            {' ', '*', ' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' ', '*', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' '},
            {' ', '*', ' ', ' ', ' ', '*', ' ', ' ', ' ', '*', ' ', '*', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' '},
            {' ', '*', ' ', ' ', ' ', '*', ' ', ' ', ' ', '*', ' ', '*', '*', '*', ' ', ' ', '*', '*', '*', ' '},
            {' ', '*', ' ', ' ', ' ', '*', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' ', ' '},
            {' ', '*', ' ', ' ', ' ', '*', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' ', ' '},
            {' ', '*', ' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' ', ' '},
            {' ', '*', '*', '*', ' ', ' ', ' ', '*', ' ', ' ', ' ', '*', '*', '*', ' ', ' ', '*', '*', '*', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            printf("%c", lose[i][j]);
            fflush(stdout);
            usleep(20000);
        }
        printf("\n");
        usleep(30000);
    }
    printf("\nDuring the game you collected coins: %d\n", coin);
    usleep(30000);
    choiceMenu();
}
// void substructHeard(){
//     for(int i = 0; i < health; i++){
//         hearts[i] = "♥";
//     }
// }
void checkColisionPortal()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == 10 && abs(j - playerX) <= 1 && abs(i - playerY) <= 1)
            {
                coin -= 20;
                portal = 0;
                map[i][j] = 0;
                startLevel2();
            }
        }
    }
}
void checkColisionBonus()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == 8 && abs(j - playerX) <= 1 && abs(i - playerY) <= 1)
            {
                coin++;
                map[i][j] = 0;
                spawnBonus();
            }
        }
    }
}
void checkColisionHeart()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == 9 && abs(j - playerX) <= 1 && abs(i - playerY) <= 1)
            {
                health++;
                heart = 0;
                map[i][j] = 0;
            }
        }
    }
}
void plant(int x, int y, int what)
{
    if (x >= 0 && x < width && y >= 0 && y < height && map[y][x] == 0)
        map[y][x] = what;
}
void randomPlant()
{
    for (int i = 0; i < 15; i++)
    {
        int x = rand() % width;
        int y = rand() % height;
        int plantType = 3 + rand() % 3;
        plant(x, y, plantType);
    }
}
void spawnEnemies()
{
    countEnemies = 3 + rand() % 10;
    for (int i = 0; i < countEnemies; i++)
    {
        int x, y;
        do
        {
            x = rand() % width;
            y = rand() % height;
        } while (map[y][x] != 0 || (x == playerX && y == playerY));

        enemyX[i] = x;
        enemyY[i] = y;
        map[y][x] = 7;
    }
}
void moveEnemies()
{
    for (int i = 0; i < countEnemies; i++)
    {
        map[enemyY[i]][enemyX[i]] = 0;

        if (moveCounter % 3 == 0)
        {
            if (enemyX[i] < playerX && map[enemyY[i]][enemyX[i] + 1] == 0)
                enemyX[i]++;
            else if (enemyX[i] > playerX && map[enemyY[i]][enemyX[i] - 1] == 0)
                enemyX[i]--;
            else if (enemyY[i] < playerY && map[enemyY[i] + 1][enemyX[i]] == 0)
                enemyY[i]++;
            else if (enemyY[i] > playerY && map[enemyY[i] - 1][enemyX[i]] == 0)
                enemyY[i]--;
        }

        map[enemyY[i]][enemyX[i]] = 7;
    }
}
void refreshEnemiesOnMap()
{
    for (int i = 0; i < countEnemies; i++)
        if (map[enemyY[i]][enemyX[i]] == 0)
            map[enemyY[i]][enemyX[i]] = 7;
}
void drawPlayer(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height && map[y][x] == 0)
        map[y][x] = 6;
}
void movePlayer(){
    char c = getchar();
            beforePlayerX = playerX;
            beforePlayerY = playerY;
            map[playerY][playerX] = 0;

            if ((c == 'w' || c == 'W') && map[playerY - 1][playerX] == 0)
                playerY--;
            else if ((c == 's' || c == 'S') && map[playerY + 1][playerX] == 0)
                playerY++;
            else if ((c == 'a' || c == 'A') && map[playerY][playerX - 1] == 0)
                playerX--;
            else if ((c == 'd' || c == 'D') && map[playerY][playerX + 1] == 0)
                playerX++;
            afterPlayerX = playerX;
            afterPlayerY = playerY;
}
void showHint()
{
    if (health == 3){
    if(level == 1)printf("%s\n", portal == 0 ? hint1 : hint2);
    }
    else if(health < 3) printf("%s\n", hint3);
    else printf("%s\n", hint4);
}
void gameLoop()
{
    char c;
    drawPlayer(playerX, playerY);
    while (1)
    {
        if (kbhit())
        {
            movePlayer();
            if ((c == 'q' || c == 'Q'))
                break;
            if (beforePlayerX == afterPlayerX && beforePlayerY == afterPlayerY)
                health--;
            if (health <= 0)
            {
                loseScreen();
                break;
            }
            else if (health < 3 && heart != 1)
            {
                spawnHeart();
                heart = 1;
            }
            if (coin >= 2 && portal == 0)
            {
                portal += 1;
                spawnPortal();
            }
            // substructHeard();
            drawPlayer(playerX, playerY);
            moveEnemies();
            moveCounter += 2;
            refreshEnemiesOnMap();
            checkColisionBonus();
            checkColisionHeart();
            checkColisionPortal();
            system("clear");
            printf("coins: %d   health: %d\n", coin, health);
            showHint();
            drawMap();
        }

        usleep(50000);
    }
}
void resetMap()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (map[y][x] != 0 && map[y][x] != 1 && map[y][x] != 2)
            {
                map[y][x] = 0;
            }
        }
    }
}
void resetVariable()
{
    playerX = 2;
    playerY = 2;
    health = 3;
    coin = 0;
    moveCounter = 0;
    countEnemies = 0;
    resetMap();
}
void startGame()
{
    system("clear");
    srand(time(NULL));
    resetVariable();
    createMapLevel1();
    randomPlant();
    spawnEnemies();
    spawnBonus();
    drawMap();
    beforePlayerX = playerX;
    beforePlayerY = playerY;
    gameLoop();
}

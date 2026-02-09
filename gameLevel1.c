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

// ================== ГЛОБАЛЬНІ ЗМІННІ ==================
const int width = 30;
const int height = 11;

int playerX = 2, playerY = 2;
int beforePlayerX, beforePlayerY;
int afterPlayerX, afterPlayerY;

int health = 3;
int coin = 0;
int heart = 0;
int portal = 0;
int level = 1;
int moveCounter = 0;

#define MAX_ENEMIES 10
int enemyX[MAX_ENEMIES];
int enemyY[MAX_ENEMIES];
int countEnemies = 0;

// ================== МАПА ==================
int mapLevel1[height][width] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int map[height][width];

// ================== МАПА ==================
void createMapLevel1() {
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            map[y][x] = mapLevel1[y][x];
}

void drawMap() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch (map[y][x]) {
                case 0: printf(" "); break;
                case 1: printf("-"); break;
                case 2: printf("|"); break;
                case 3: printf("\033[36m*\033[0m"); break;
                case 4: printf("\033[92m\u2663\033[0m"); break;
                case 5: printf("\u26F0"); break;
                case 6: printf("⛹"); break;
                case 7: printf("\033[31m@\033[0m"); break;
                case 8: printf("\033[93m\u25C9\033[0m"); break;
                case 9: printf("\033[31m\u2665\033[0m"); break;
                case 10: printf("#"); break;
                default: printf("?"); break;
            }
        }
        printf("\n");
    }
}

// ================== СПАВН ОБʼЄКТІВ ==================
void plant(int x, int y, int what) {
    if (x >= 0 && x < width && y >= 0 && y < height && map[y][x] == 0)
        map[y][x] = what;
}

void spawnRandom(int type) {
    int x, y;
    do {
        x = rand() % width;
        y = rand() % height;
    } while (map[y][x] != 0);
    plant(x, y, type);
}

void randomPlant() {
    for (int i = 0; i < 15; i++)
        spawnRandom(3 + rand() % 3);
}

// ================== ГРАВЕЦЬ ==================
void drawPlayer() {
    map[playerY][playerX] = 6;
}

void movePlayer() {
    char c = getchar();

    beforePlayerX = playerX;
    beforePlayerY = playerY;
    map[playerY][playerX] = 0;

    if ((c == 'w' || c == 'W') && map[playerY - 1][playerX] == 0) playerY--;
    else if ((c == 's' || c == 'S') && map[playerY + 1][playerX] == 0) playerY++;
    else if ((c == 'a' || c == 'A') && map[playerY][playerX - 1] == 0) playerX--;
    else if ((c == 'd' || c == 'D') && map[playerY][playerX + 1] == 0) playerX++;

    afterPlayerX = playerX;
    afterPlayerY = playerY;
}

// ================== ВОРОГИ ==================
void spawnEnemies() {
    countEnemies = 3 + rand() % 5;
    for (int i = 0; i < countEnemies; i++)
        spawnRandom(7);
}

void moveEnemies() {
    if (moveCounter++ % 3 != 0) return;

    for (int i = 0; i < countEnemies; i++) {
        map[enemyY[i]][enemyX[i]] = 0;

        if (enemyX[i] < playerX) enemyX[i]++;
        else if (enemyX[i] > playerX) enemyX[i]--;
        else if (enemyY[i] < playerY) enemyY[i]++;
        else if (enemyY[i] > playerY) enemyY[i]--;

        map[enemyY[i]][enemyX[i]] = 7;
    }
}

// ================== ЛОГІКА ==================
void updateHealth() {
    if (beforePlayerX == afterPlayerX && beforePlayerY == afterPlayerY)
        health--;

    if (health <= 0)
        loseScreen();
}

void updateGameObjects() {
    if (coin >= 2 && portal == 0) {
        portal = 1;
        spawnRandom(10);
    }
}

void render() {
    system("clear");
    printf("coins: %d   health: %d\n", coin, health);
    drawMap();
}

// ================== GAME LOOP ==================
void gameLoop() {
    drawPlayer();

    while (health > 0) {
        if (kbhit()) {
            movePlayer();
            updateHealth();
            updateGameObjects();
            moveEnemies();
            drawPlayer();
            render();
        }
        usleep(50000);
    }
}

// ================== СТАРТ ==================
void resetGame() {
    playerX = 2;
    playerY = 2;
    health = 3;
    coin = 0;
    moveCounter = 0;
}

void startGame() {
    system("clear");
    srand(time(NULL));

    resetGame();
    createMapLevel1();
    randomPlant();
    spawnEnemies();
    spawnRandom(8);

    drawMap();
    gameLoop();
}

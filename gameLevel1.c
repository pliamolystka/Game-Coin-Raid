// ================== INCLUDES ==================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "controlPlayer.h"
#include "gameLevel2.h"
#include "menu.h"
#include "hint.h"

// ================== CONSTANTS ==================
#define WIDTH 30
#define HEIGHT 11
#define MAX_ENEMIES 10

// ================== GLOBAL ==================
int playerX = 2, playerY = 2;
int beforePlayerX, beforePlayerY;
int afterPlayerX, afterPlayerY;

int health = 3;
int coin = 0;
int heart = 0;
int portal = 0;
int level = 1;

int moveCounter = 0;

int enemyX[MAX_ENEMIES];
int enemyY[MAX_ENEMIES];
int countEnemies = 0;

int map[HEIGHT][WIDTH];

// ================== BASE MAP ==================
int mapLevel1[HEIGHT][WIDTH] = {
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

// ================== MAP ==================
void initMap() {
    for(int y=0;y<HEIGHT;y++)
        for(int x=0;x<WIDTH;x++)
            map[y][x]=mapLevel1[y][x];
}

int isFree(int x,int y){
    return x>=0 && x<WIDTH && y>=0 && y<HEIGHT && map[y][x]==0;
}

void placeOnMap(int x,int y,int type){
    if(isFree(x,y)) map[y][x]=type;
}

// ================== SPAWN ==================
void spawnObject(int type){
    int x,y;
    do{
        x=rand()%WIDTH;
        y=rand()%HEIGHT;
    }while(!isFree(x,y));

    placeOnMap(x,y,type);
}

// ================== DRAW ==================
void drawMap(){
    for(int y=0;y<HEIGHT;y++){
        for(int x=0;x<WIDTH;x++){
            switch(map[y][x]){
                case 0: printf(" "); break;
                case 1: printf("-"); break;
                case 2: printf("|"); break;
                case 6: printf("⛹"); break;
                case 7: printf("@"); break;
                case 8: printf("○"); break;
                case 9: printf("♥"); break;
                case 10: printf("#"); break;
                default: printf("?"); break;
            }
        }
        printf("\n");
    }
}

// ================== PLAYER ==================
void drawPlayer(){
    placeOnMap(playerX,playerY,6);
}

void movePlayer(){
    char c=getchar();

    beforePlayerX=playerX;
    beforePlayerY=playerY;

    map[playerY][playerX]=0;

    if((c=='w'||c=='W')&&isFree(playerX,playerY-1)) playerY--;
    if((c=='s'||c=='S')&&isFree(playerX,playerY+1)) playerY++;
    if((c=='a'||c=='A')&&isFree(playerX-1,playerY)) playerX--;
    if((c=='d'||c=='D')&&isFree(playerX+1,playerY)) playerX++;

    afterPlayerX=playerX;
    afterPlayerY=playerY;
}

// ================== ENEMIES ==================
void spawnEnemies(){
    countEnemies=3+rand()%5;

    for(int i=0;i<countEnemies;i++){
        spawnObject(7);
        enemyX[i]=playerX;
        enemyY[i]=playerY;
    }
}

void moveEnemies(){
    if(moveCounter++%3!=0) return;

    for(int i=0;i<countEnemies;i++){

        map[enemyY[i]][enemyX[i]]=0;

        if(enemyX[i]<playerX) enemyX[i]++;
        else if(enemyX[i]>playerX) enemyX[i]--;
        else if(enemyY[i]<playerY) enemyY[i]++;
        else if(enemyY[i]>playerY) enemyY[i]--;

        placeOnMap(enemyX[i],enemyY[i],7);
    }
}

// ================== LOGIC ==================
void updateHealth(){

    if(beforePlayerX==afterPlayerX &&
       beforePlayerY==afterPlayerY)
        health--;

    if(health<=0) loseScreen();
}

void updateObjects(){

    if(coin>=2 && portal==0){
        portal=1;
        spawnObject(10);
    }

    if(health<3 && heart==0){
        heart=1;
        spawnObject(9);
    }
}

void render(){
    system("clear");
    printf("Coins: %d  Health: %d\n",coin,health);
    drawMap();
}

// ================== GAME LOOP ==================
void gameLoop(){

    drawPlayer();

    while(health>0){

        if(kbhit()){

            movePlayer();
            updateHealth();
            updateObjects();
            moveEnemies();

            drawPlayer();
            render();
        }

        usleep(50000);
    }
}

// ================== START ==================
void resetGame(){
    playerX=2;
    playerY=2;
    health=3;
    coin=0;
    moveCounter=0;
    portal=0;
    heart=0;
}

void startGame(){

    system("clear");
    srand(time(NULL));

    resetGame();
    initMap();

    spawnEnemies();
    spawnObject(8);

    drawMap();
    gameLoop();
}

#ifndef GAMELEVEL1_H
#define GAMELEVEL1_H
#ifdef __cplusplus
extern "C" {
#endif
extern const int width;
extern const int height;
extern int playerX;
extern int playerY;
extern int beforePlayerX;
extern int beforePlayerY;
extern int afterPlayerX;
extern int afterPlayerY;
extern int health;
extern const char *hearts[3];
extern int coin;
extern int moveCounter;
extern int enemyX[];
extern int enemyY[];
extern int countEnemies;
extern int map[11][30];
extern int tmpMap[11][30];
void drawMap();
void drawHeart(int x, int y);
void drawBonus(int x, int y);
void spawnBonus();
void spawnHeart();
void loseScreen();
void checkColisionHeart();;
void checkColisionBonus();
void plant(int x, int y, int what);
void randomPlant();
void spawnEnemies();
void moveEnemies();
void refreshEnemiesOnMap();
void drawPlayer(int x, int y);
void gameLoop();
void resetMap();
void resetVariable();
void startGame();

#ifdef __cplusplus
}
#endif
#endif

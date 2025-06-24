#ifndef MENU_H
#define MENU_H
#ifdef __cplusplus
extern "C" {
#endif
extern char startTheNewGame[20];
extern char Rules[8];
extern char Author[9];
int getch(void);
void drawMenu(int choice);
void choiceMenu();
#ifdef __cplusplus
}
#endif
#endif
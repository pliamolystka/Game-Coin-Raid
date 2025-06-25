#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
void drawRules()
{
    system("clear");
    printf("--------------------------------- Rules ---------------------------------------\n\n");
    printf(" Welcome to the \033[33mCoin Raid\033[0m game rules section.\n");
    printf(" The goal of the game is to survive in a hostile arena, avoiding enemies and obstacles,\n collecting bonuses and hearts to score as many coins as possible.\n");
    printf(" The player controls a character (⛹) using the arrow keys, who moves around the map.\n");
    printf(" If health (♥) reaches 0, the game ends - a defeat screen appears\n");
    printf(" The goal is to collect as many coins as possible before enemies catch up with you or you lose all your health.\n");
    printf(" Hearts can be found and picked up to restore health if you have less than 3 hp.\n");
    printf(" Obstacles (*, ♣, 🗻) — hinder movement and complicate the path.");
    
}
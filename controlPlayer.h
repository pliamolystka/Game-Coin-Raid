#ifndef CONTROL_PLAYER_H
#define CONTROL_PLAYER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// Оголошення функцій
void setNonCanonicalMode(int enable);
int kbhit(void);

#ifdef __cplusplus
}
#endif

#endif // CONTROL_PLAYER_H
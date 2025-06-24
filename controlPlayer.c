#include "controlPlayer.h"

void setNonCanonicalMode(int enable)
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    if (enable)
    {
        t.c_lflag &= ~(ICANON | ECHO);
    }
    else
    {
        t.c_lflag |= (ICANON | ECHO);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    setNonCanonicalMode(1);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    fcntl(STDIN_FILENO, F_SETFL, oldf);
    setNonCanonicalMode(0);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
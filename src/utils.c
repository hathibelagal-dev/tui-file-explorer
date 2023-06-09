#include "utils.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "state.h"
#include "components.h"

struct termios modified_config;
struct termios original_config;
struct winsize window_size;

void setupConsole()
{
    tcgetattr(0, &modified_config);
    tcgetattr(0, &original_config);
    modified_config.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &modified_config);
    ioctl(fileno(stdout), TIOCGWINSZ, &window_size);
}

void hideCursor()
{
    printf("%c?25l", ESC);
}

void resetCursor()
{
    printf("%c[2J%c[;H", ESC, ESC);
}

void resetConsole()
{
    resetCursor();
    tcsetattr(fileno(stdin), TCSANOW, &original_config);
}

void startLoop()
{
    char input = 0;
    while (input != 'q')
    {
        render();
        input = getchar();
    }
    resetConsole();
}

void render()
{
    ioctl(fileno(stdout), TIOCGWINSZ, &window_size);
    if (window_size.ws_col != state.n_cols)
    {
        state.n_cols = window_size.ws_col;
        updateState();
    }
    renderWindow(window_size.ws_row, window_size.ws_col);
}

#include "utils.h"
#include <stdio.h>
#include <termios.h>
#include "components.h"

struct termios modified_config;
struct termios original_config;

void setupConsole()
{
    tcgetattr(0, &modified_config);
    tcgetattr(0, &original_config);
    modified_config.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &modified_config);
}

void resetConsole()
{
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
    renderWindow();
}

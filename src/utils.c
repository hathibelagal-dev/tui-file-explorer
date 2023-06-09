#include "utils.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "state.h"
#include <string.h>
#include "components.h"
#include <unistd.h>
#include "styles.h"

struct termios modified_config;
struct termios original_config;
struct winsize window_size;

void setup_console()
{
    tcgetattr(0, &modified_config);
    tcgetattr(0, &original_config);
    modified_config.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &modified_config);
    ioctl(fileno(stdout), TIOCGWINSZ, &window_size);
}

void hide_cursor()
{
    printf("%c?25l", ESC);
}

void get_pos(char *str, int row, int col)
{
    sprintf(str, "%c[%d;%dH", ESC, row, col);
}

void goto_directory(const char *path)
{
    int result = chdir(path);
    if (result != 0)
    {
        return;
    }
    strcpy(state.prev_path, state.current_path);
    update_state();
}

void reset_cursor()
{
    printf("%c[2J%c[;H%c%s", ESC, ESC, ESC, RESET);
}

void reset_console()
{
    reset_cursor();
    tcsetattr(fileno(stdin), TCSANOW, &original_config);
}

void start_loop()
{
    char input = 0;
    while (input != 'q')
    {
        if (input == 'p')
        {
            goto_directory("..");
        }
        if (input == 'b')
        {
            goto_directory(state.prev_path);
        }
        render();
        input = getchar();
    }
    reset_console();
}

void render()
{
    ioctl(fileno(stdout), TIOCGWINSZ, &window_size);
    if (window_size.ws_col != state.n_cols)
    {
        state.n_cols = window_size.ws_col;
        update_state();
    }
    render_window(window_size.ws_row, window_size.ws_col);
}

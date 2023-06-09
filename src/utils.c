/*
 * This file is part of tui-file-explorer
 * Copyright (c) 2023 Ashraff Hathibelagal
 *
 * tui-file-explorer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * tui-file-explorer is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with tui-file-explorer. If not, see <https://www.gnu.org/licenses/>.
 */

#define _DEFAULT_SOURCE
#include "utils.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "state.h"
#include <string.h>
#include "components.h"
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
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
    printf("%c[?25l", ESC);
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
    bool valid = true;
    while (input != 'q')
    {
        switch (input)
        {
        case 'p':
            goto_directory("..");
            valid = true;
            break;
        case 'b':
            goto_directory(state.prev_path);
            valid = true;
            break;
        case 'w':
            state.selected_index -= 1;
            if (state.selected_index < 0)
            {
                state.selected_index = 0;
            }
            valid = true;
            break;
        case 's':
            state.selected_index += 1;
            if (state.selected_index >= state.n_entries - 1)
            {
                state.selected_index = state.n_entries - 1;
            }
            valid = true;
            break;
        case 'r':
            valid = true;
            break;
        case ' ':
            if (state.entries[state.selected_index].entry_type == DT_DIR)
            {
                char new_path[MAX_PATH_LEN];
                sprintf(new_path, "./%s", state.entries[state.selected_index].entry_name);
                goto_directory(new_path);
            }
            valid = true;
            break;
        }
        if (valid)
        {
            render();
            valid = false;
        }
        input = getchar();
    }
    reset_console();
}

void render()
{
    ioctl(fileno(stdout), TIOCGWINSZ, &window_size);
    if (window_size.ws_col != state.n_cols || window_size.ws_row != state.n_rows)
    {
        state.n_cols = window_size.ws_col;
        state.n_rows = window_size.ws_row;
        update_state();
    }
    render_window(window_size.ws_row, window_size.ws_col);
}

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

#include <stdbool.h>

#ifndef UTILS
#define UTILS
#define MAX_PATH_LEN 512
#define MAX_FILE_LEN 64
#define MAX_FILES 1024
#define MAX_FILE_DISPLAY_ITEM_LEN 35
#define MAX_FILE_TYPE_LEN 256
#define MAX_FILE_CONTENTS_LEN 256
#define GAP 13
#define ESC 27
#define POS_SIZE 16
#endif

void setup_console(void);
void start_loop(void);
void hide_cursor(void);
void show_cursor(void);
void reset_cursor(void);
void reset_console(void);
void render(void);
void get_pos(char *str, int v, int h);
bool goto_directory(const char *path);

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

#ifndef UTILS
#define UTILS
#define MAX_PATH_LEN 512
#define MAX_FILE_LEN 64
#define MAX_FILES 1024
#define GAP 13
#define ESC 27
#define POS_SIZE 16
#endif

void setup_console();
void start_loop();
void hide_cursor();
void reset_cursor();
void reset_console();
void render();
void get_pos(char *str, int v, int h);
void goto_directory(const char *);

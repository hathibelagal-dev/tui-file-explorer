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

#include <magic.h>
#ifndef FILEPROC
#define FILEPROC
magic_t magic_cookie;
#endif

void init_magic(void);
void close_magic(void);
void get_file_type(const char *file_name, char *output);
void get_file_contents(const char *file_name, char *output);
void get_file_size(const char *file_name, long *size);
void update_file_type_and_contents(void);
void resetCounts(void);
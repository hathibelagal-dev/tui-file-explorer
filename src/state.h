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

#include "utils.h"

#ifndef STATE
#define STATE
struct dir_entry_info
{
    char entry_name[MAX_FILE_LEN];
    unsigned char entry_type;
};

struct fex_state
{
    char current_path[MAX_PATH_LEN];
    char prev_path[MAX_PATH_LEN];

    int n_files;
    int n_directories;
    int n_entries;
    int n_symlinks;
    int list_top;
    int selected_index;
    bool at_home;
    bool has_file_type;
    struct dir_entry_info entries[MAX_FILES];
    char current_file_type[MAX_FILE_TYPE_LEN];
    char current_file_contents[MAX_FILE_CONTENTS_LEN];

    int n_cols;
    int n_rows;
};

struct fex_state state;
#endif

void set_current_path(void);
void update_state(void);
void set_directory_contents(void);

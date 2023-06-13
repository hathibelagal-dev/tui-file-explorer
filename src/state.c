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
#include "state.h"
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

void set_current_path()
{
    char *path;
    path = getcwd(path, MAX_PATH_LEN);
    int n = strlen(path);
    int max_current_len = state.n_cols - GAP;
    if (n > max_current_len)
    {
        sprintf(state.current_path, "…%s", path + n - max_current_len);
    }
    else
    {
        strcpy(state.current_path, path);
    }
}

void set_directory_contents()
{
    DIR *dir = opendir(".");
    state.n_entries = 0;
    state.n_files = 0;
    state.n_directories = 0;
    state.n_symlinks = 0;
    state.list_top = 0;
    state.selected_index = 0;
    int i = 0;
    for (;;)
    {
        struct dirent *details = readdir(dir);
        if (details != NULL && state.n_entries < MAX_FILES)
        {
            if (strcmp(details->d_name, ".") == 0 || strcmp(details->d_name, "..") == 0)
            {
                continue;
            }
            state.n_entries += 1;
            strcpy(state.entries[i].entry_name, details->d_name);
            state.entries[i].entry_type = details->d_type;
            switch (details->d_type)
            {
            case DT_REG:
                state.n_files += 1;
                break;
            case DT_DIR:
                state.n_directories += 1;
                break;
            case DT_LNK:
                state.n_symlinks += 1;
                break;
            }
            i++;
        }
        else
        {
            break;
        }
    }
}

void update_state()
{
    set_current_path();
    set_directory_contents();
}
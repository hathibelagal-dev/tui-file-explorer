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
#include "file_processor.h"
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "state.h"
#include <stdlib.h>
#include <sys/stat.h>

void init_magic()
{
    magic_cookie = magic_open(MAGIC_NONE);
    magic_load(magic_cookie, NULL);
}

void close_magic()
{
    magic_close(magic_cookie);
}

void resetCounts()
{
    state.current_file_size = 0;
    state.content_bytes_read = 0;
}

void update_file_type_and_contents()
{
    char full_path[MAX_PATH_LEN];
    if (state.n_entries == 0)
    {
        strcpy(state.current_file_contents, "");
        strcpy(state.current_file_type, "");
        resetCounts();
        return;
    }
    if (state.entries[state.selected_index].entry_type == DT_REG)
    {
        sprintf(full_path, "./%s", state.entries[state.selected_index].entry_name);
        get_file_type(full_path, state.current_file_type);
        get_file_contents(full_path, state.current_file_contents);
        get_file_size(full_path, &state.current_file_size);
        state.has_file_type = true;
    }
    else if (state.entries[state.selected_index].entry_type == DT_DIR)
    {
        strcpy(state.current_file_type, "directory");
        strcpy(state.current_file_contents, "");
        state.has_file_type = true;
        resetCounts();
    }
    else
    {
        strcpy(state.current_file_type, "🙈");
        strcpy(state.current_file_contents, "");
        state.has_file_type = false;
        resetCounts();
    }
}

void get_file_type(const char *file_name, char *output)
{
    const char *file_type = magic_file(magic_cookie, file_name);
    if (file_type != NULL)
    {
        strcpy(output, file_type);
    }
    else
    {
        strcpy(output, "Unknown file type");
    }
}

void get_file_contents(const char *file_name, char *output)
{
    FILE *fp = fopen(file_name, "rb");
    const size_t n_bytes = fread(output, sizeof(char), MAX_FILE_CONTENTS_LEN, fp);
    output[n_bytes] = '\0';
    state.content_bytes_read = n_bytes;
    fclose(fp);
}

void get_file_size(const char *file_name, long *size)
{
    struct stat st;
    stat(file_name, &st);
    *size = st.st_size;
}

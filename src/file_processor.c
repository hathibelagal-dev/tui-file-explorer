#define _DEFAULT_SOURCE
#include "file_processor.h"
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "state.h"
#include <stdlib.h>

void init_magic()
{
    magic_cookie = magic_open(MAGIC_NONE);
    magic_load(magic_cookie, NULL);
}

void close_magic()
{
    magic_close(magic_cookie);
}

void update_file_type()
{
    char full_path[MAX_PATH_LEN * 2];
    if (state.entries[state.selected_index].entry_type == DT_REG)
    {
        sprintf(full_path, "%s/%s",
                state.current_path, state.entries[state.selected_index].entry_name);
        get_file_type(full_path, state.current_file_type);
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
}

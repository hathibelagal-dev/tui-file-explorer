#define _DEFAULT_SOURCE
#include "state.h"
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

void set_current_path()
{
    char path[MAX_PATH_LEN];
    getcwd(path, MAX_PATH_LEN);
    int n = strlen(path);
    int max_current_len = state.n_cols - GAP;
    if (n > max_current_len)
    {
        sprintf(state.current_path, "...%s", path + n - max_current_len);
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
    int i = 0;
    for (;;)
    {
        struct dirent *details = readdir(dir);
        if (details != NULL && state.n_entries < MAX_FILES)
        {
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
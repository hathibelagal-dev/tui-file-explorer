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
}

void update_state()
{
    set_current_path();
    set_directory_contents();
}
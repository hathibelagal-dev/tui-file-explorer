#include "utils.h"

#ifndef STATE
#define STATE
struct fex_state
{
    char current_path[MAX_PATH_LEN];
    int n_files;
    int n_directories;
    int n_cols;
};

struct fex_state state;
#endif

void updateState();

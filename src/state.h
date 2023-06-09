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
    long space_occupied;
    struct dir_entry_info entries[MAX_FILES];

    int n_cols;
};

struct fex_state state;
#endif

void update_state();

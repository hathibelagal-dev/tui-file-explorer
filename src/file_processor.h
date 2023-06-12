#include <magic.h>
#ifndef FILEPROC
#define FILEPROC
magic_t magic_cookie;
#endif

void init_magic(void);
void close_magic(void);
void get_file_type(const char *file_name, char *output);
void get_file_contents(const char *file_name, char *output);
void update_file_type(void);
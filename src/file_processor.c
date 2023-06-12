#include <magic.h>
#include <string.h>

void get_file_type(const char *file_name, char *output)
{
    magic_t cookie = magic_open(MAGIC_NONE);
    const char *file_type = magic_file(cookie, file_name);
    strcpy(output, file_type == NULL ? file_type : "Unknown type of file.");
    magic_close(cookie);
}

void get_file_contents(const char *file_name, char *output)
{
}
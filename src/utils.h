#ifndef UTILS
#define UTILS
#define MAX_PATH_LEN 512
#define MAX_FILE_LEN 64
#define MAX_FILES 1024
#define GAP 13
#define ESC 27
#endif

void setup_console();
void start_loop();
void hide_cursor();
void reset_cursor();
void reset_console();
void render();
void get_pos(char *str, int v, int h);
void goto_parent_directory(const char *);

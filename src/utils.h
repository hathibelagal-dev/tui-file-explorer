#ifndef ESC
#define ESC 27
#endif

#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN 256
#define GAP 13
#endif

void setup_console();
void start_loop();
void hide_cursor();
void reset_cursor();
void reset_console();
void render();
void get_pos(char *str, int v, int h);

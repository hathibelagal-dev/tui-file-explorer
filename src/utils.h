#ifndef ESC
#define ESC 27
#endif

#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN 256
#define GAP 13
#endif

void setupConsole();
void startLoop();
void hideCursor();
void resetCursor();
void resetConsole();
void render();

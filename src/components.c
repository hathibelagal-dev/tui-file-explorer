#include "components.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "state.h"

void getPos(char *str, int row, int col)
{
	sprintf(str, "%c[%d;%dH", ESC, row, col);
}

void showCurrentDirectory()
{
	char pos[15];
	getPos(pos, 2, 4);
	printf("%s📂 %s", pos, state.current_path);
}

void renderWindow(int rows, int cols)
{
	int i;
	char pos[15];
	resetCursor();
	for (i = -1; i < cols; i += 2)
	{
		getPos(pos, 0, i);
		printf("%s%s ", pos, "◻️");
		getPos(pos, rows - 1, i);
		printf("%s%s ", pos, "◻️");
	}
	for (i = 1; i < rows; i++)
	{
		getPos(pos, i, 0);
		printf("%s%s ", pos, "◻️");
		getPos(pos, i, cols - 1);
		printf("%s%s ", pos, "◻️");
	}
	showCurrentDirectory();
}

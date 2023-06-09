#include "components.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void getPos(char *str, int v, int h)
{
	sprintf(str, "%c[%d;%dH", ESC, v, h);
}

void renderWindow()
{
	int i;
	char pos[15];
	printf("%c[2J%c[;H", ESC, ESC);
	for (i = -1; i < COLS; i += 2)
	{
		getPos(pos, 0, i);
		printf("%s%s ", pos, "◻️");
		getPos(pos, ROWS - 1, i);
		printf("%s%s ", pos, "◻️");
	}
	for (i = 1; i < ROWS; i++)
	{
		getPos(pos, i, 0);
		printf("%s%s ", pos, "◻️");
		getPos(pos, i, COLS - 1);
		printf("%s%s ", pos, "◻️");
	}
}

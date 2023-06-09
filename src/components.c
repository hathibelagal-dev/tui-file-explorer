#include "components.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "styles.h"
#include <stdbool.h>
#include "state.h"

void show_current_directory_header()
{
	char pos[15];
	get_pos(pos, 2, 4);
	printf("%s📂 %c%s%c%s%s", pos, ESC, BLUE, ESC, BOLD, state.current_path);
	get_pos(pos, 3, 4);
	printf("%c%s%s", ESC, RESET, pos);
	bool empty = true;
	if (state.n_files)
	{
		printf("Files: %c%s%d ", ESC, BOLD, state.n_files);
		printf("%c%s", ESC, RESET);
		empty = false;
	}
	if (state.n_directories)
	{
		printf("Subdirectories: %c%s%d ", ESC, BOLD, state.n_directories - 2);
		printf("%c%s", ESC, RESET);
		empty = false;
	}
	if (state.n_symlinks)
	{
		printf("Symlinks: %c%s%d ", ESC, BOLD, state.n_symlinks);
		printf("%c%s", ESC, RESET);
		empty = false;
	}
	if (empty)
	{
		printf("🤷 Empty directory");
	}
}

void render_window(int rows, int cols)
{
	int i;
	char pos[16];
	reset_cursor();
	for (i = -1; i < cols; i += 2)
	{
		get_pos(pos, 0, i);
		printf("%s%s ", pos, "◻️");
		get_pos(pos, rows - 1, i);
		printf("%s%s ", pos, "◻️");
	}
	for (i = 1; i < rows; i++)
	{
		get_pos(pos, i, 0);
		printf("%s%s ", pos, "◻️");
		get_pos(pos, i, cols - 1);
		printf("%s%s ", pos, "◻️");
	}
	show_current_directory_header();
}

/*
 * This file is part of tui-file-explorer
 * Copyright (c) 2023 Ashraff Hathibelagal
 *
 * tui-file-explorer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * tui-file-explorer is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with tui-file-explorer. If not, see <https://www.gnu.org/licenses/>.
 */

#include "components.h"
#define _DEFAULT_SOURCE
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "styles.h"
#include <stdbool.h>
#include <dirent.h>
#include "state.h"

void show_current_directory_header(int rows, int cols)
{
	char pos[POS_SIZE];
	int i = 0;
	bool empty = true;
	get_pos(pos, 2, 4);
	printf("%s📂 %c%s%c%s%s", pos, ESC, BLUE, ESC, BOLD, state.current_path);
	get_pos(pos, 3, 7);
	printf("%c%s%s", ESC, RESET, pos);
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
	get_pos(pos, 4, 3);
	printf("%s", pos);
	for (; i < cols - 4; i++)
	{
		printf("-");
	}
}

void show_directory_contents(int rows)
{
	char pos[POS_SIZE];
	int i = 5;
	int j = state.list_top;

	for (; i < rows - 4; i += 2)
	{
		get_pos(pos, i, 4);
		printf("%s", pos);
		switch (state.entries[j].entry_type)
		{
		case DT_DIR:
			printf("📁 ");
			break;
		case DT_REG:
			printf("📄 ");
			break;
		case DT_LNK:
			printf("🔗 ");
			break;
		}
		printf("%s", state.entries[j].entry_name);
		j += 1;
		if (j >= state.n_entries)
		{
			break;
		}
	}
}

void render_window(int rows, int cols)
{
	int i;
	char pos[POS_SIZE];
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
	show_current_directory_header(rows, cols);
	show_directory_contents(rows);
}

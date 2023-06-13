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
#include <string.h>
#include <ctype.h>
#include "state.h"

#define RIGHT_PANEL_GAP 8
#define HEADER_HEIGHT 4

int show_file_type(int cols)
{
	int starting_col = MAX_FILE_DISPLAY_ITEM_LEN + RIGHT_PANEL_GAP;
	int c_row = HEADER_HEIGHT + 1;
	int c_idx = 0;
	int c_col = starting_col;
	if (state.n_entries == 0)
	{
		return c_row + 1;
	}
	int n = strlen(state.current_file_type);
	char *label = "File type: ";
	int label_n = strlen(label);
	char pos[POS_SIZE];
	get_pos(pos, c_row, c_col);
	printf("%s%c%s%s%c%s", pos, ESC, BOLD, label, ESC, RESET);
	if (!state.has_file_type)
	{
		printf("%s", state.current_file_type);
	}
	else
	{
		c_col += label_n;
		for (; c_idx < n; c_idx++)
		{
			char current_character = state.current_file_type[c_idx];
			if (c_col == starting_col && isspace(current_character))
			{
				continue;
			}
			if (isspace(current_character) || isprint(current_character))
			{
				get_pos(pos, c_row, c_col);
				printf("%s%c", pos, current_character);
				c_col += 1;
				if (c_col > cols - 3)
				{
					c_col = starting_col;
					c_row += 1;
				}
			}
		}
	}
	c_row += 1;
	c_col = starting_col - 1;
	while (c_col < cols - 1)
	{
		get_pos(pos, c_row, c_col);
		printf("%s%c", pos, '-');
		c_col += 1;
	}
	return c_row + 1;
}

void show_current_directory_header(int rows, int cols)
{
	char pos[POS_SIZE];
	int i = 0;
	bool empty = true;
	get_pos(pos, 2, 4);
	printf("%s", pos);
	if (state.at_home)
	{
		printf("🏠 ");
	}
	else
	{
		printf("📂 ");
	}
	printf("%c%s%c%s%s", ESC, BLUE, ESC, BOLD, state.current_path);
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
		printf("Subdirectories: %c%s%d ", ESC, BOLD, state.n_directories);
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
		printf("🤷 Empty directory 👻👻");
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
	int i = HEADER_HEIGHT + 1;
	int j;
	int max_visible = rows - 2;
	int highest_visible_index = max_visible / 2 - 3;
	int padding_len;
	int k;

	if (state.selected_index >= highest_visible_index)
	{
		state.list_top = state.selected_index - highest_visible_index;
	}
	j = state.list_top;
	if (state.n_entries > 0)
	{
		for (; i < max_visible; i += 2)
		{
			get_pos(pos, i, 4);
			printf("%s", pos);
			padding_len = MAX_FILE_DISPLAY_ITEM_LEN - (3 + strlen(state.entries[j].entry_name));
			if (j == state.selected_index)
			{
				printf("%c%s", ESC, BG_GREEN);
			}
			switch (state.entries[j].entry_type)
			{
			case DT_DIR:
				printf(" 📁 ");
				break;
			case DT_REG:
				printf(" 📄 ");
				break;
			case DT_LNK:
				printf(" 🔗 ");
				break;
			}
			char *file_name = state.entries[j].entry_name;
			int file_name_len = strlen(file_name);
			if (file_name_len >= MAX_FILE_DISPLAY_ITEM_LEN)
			{
				file_name += file_name_len - (MAX_FILE_DISPLAY_ITEM_LEN - 6);
				printf("…");
			}
			printf("%s", file_name);
			if (j == state.selected_index)
			{
				for (k = 0; k < padding_len; k++)
				{
					putchar(' ');
				}
				printf("%c%s", ESC, RESET);
			}
			j += 1;
			if (j >= state.n_entries)
			{
				break;
			}
		}
	}
	hide_cursor();
}

void show_file_contents(int starting_row, int rows, int cols)
{
	int starting_col = MAX_FILE_DISPLAY_ITEM_LEN + RIGHT_PANEL_GAP;
	char pos[POS_SIZE];
	int c_idx = 0;
	int c_col = starting_col;
	int c_row = starting_row;
	int n = strlen(state.current_file_contents);
	if (n == 0)
	{
		return;
	}
	get_pos(pos, c_row, c_col);
	printf("%s%c%s🕵️  Hex preview %c%s", pos, ESC, BOLD, ESC, RESET);
	c_row += 2;
	for (; c_idx < n; c_idx++)
	{
		get_pos(pos, c_row, c_col);
		if (state.current_file_contents[c_idx] < 1)
		{
			continue;
		}
		printf("%s%02x ", pos, state.current_file_contents[c_idx]);
		c_col += 3;
		if (c_col > cols - 4)
		{
			c_col = starting_col;
			c_row += 1;
			if (c_row > rows - 3)
			{
				break;
			}
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
		if (i > 4)
		{
			get_pos(pos, i, MAX_FILE_DISPLAY_ITEM_LEN + 5);
			printf("%s%s", pos, "◻️");
		}
	}
	show_current_directory_header(rows, cols);
	show_directory_contents(rows);
	show_file_contents(show_file_type(cols), rows, cols);
}

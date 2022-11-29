#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"conio2.h"
#include<cstdbool>;
#include"board.h"

void Board::FillBoard()
{
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size; x++)
		{
			*(plane + y * board_size + x) = '+';
		}
	}
	
}

void Board::DisplayBoard()
{
	textbackground(YELLOW);
	textcolor(BLACK);
	int current_cursor_x = start_cursor_x, current_cursor_y = start_cursor_y;
	gotoxy(current_cursor_x, current_cursor_y);
	cputs("+");
	for (int x = 0; x < board_size * 2 + 1; x++)
	{
		putch('-');
	}
	putch('+');
	gotoxy(current_cursor_x, ++current_cursor_y);

	for (int y = 0; y < board_size; y++)
	{
		cputs("| ");
		for (int x = 0; x < board_size; x++)
		{
			putch(*(plane + y * board_size + x));
			putch(' ');

		}
		putch('|');
		current_cursor_x = start_cursor_x;
		gotoxy(current_cursor_x, ++current_cursor_y);
	}
	current_cursor_x = start_cursor_x;
	gotoxy(current_cursor_x, current_cursor_y++);
	cputs("+");
	for (int x = 0; x < board_size * 2 + 1; x++)
	{
		putch('-');
	}
	putch('+');
	
}


void Board::ChangeSize()
{
	plane = (char*)realloc(plane, board_size * board_size * sizeof(plane));
}

void Board::Draw(int _board_size, int _start_cursorx_location, int _start_cursory_location)
{
	board_size = _board_size;
	start_cursor_x = _start_cursorx_location;
	start_cursor_y = _start_cursory_location;
	ChangeSize();
	FillBoard();
	DisplayBoard();
}

void Board::Delete()
{
	//delete(*ptr_plane);
	delete(plane);
}

Board::Board(int _board_size, int _start_cursorx, int _start_cursor_y): board_size(_board_size), start_cursor_x(_start_cursorx), start_cursor_y(_start_cursor_y)
{
	plane = (char*)(board_size * board_size * sizeof(char));
	//ptr_plane = &plane;
}

Board::Board() : board_size(0), start_cursor_x(0), start_cursor_y(0) {};

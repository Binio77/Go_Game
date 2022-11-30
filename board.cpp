#include"board.h"
#include"stone.h"
#include"conio2.h"
#include<stdio.h>
#include<stdlib.h>
#include<cstdbool>;



Board::~Board()
{
	delete(plane);
}

Board::Board(int _board_size, int _start_cursorx, int _start_cursor_y) : board_size(_board_size), start_cursor_x(_start_cursorx), start_cursor_y(_start_cursor_y)
{
	plane = (Stone*)malloc(board_size * board_size * sizeof(Stone));
}


Board::Board() : board_size(0), start_cursor_x(0), start_cursor_y(0) {};

void Board::FillBoard()
{
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size; x++)
		{
			(plane + y * board_size + x)->stone_is_here = false;
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
			if ((plane + y * board_size + x)->stone_is_here == false)
				putch('+');
			else
				putch('%');

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
	plane = (Stone*)realloc(plane, board_size * board_size * sizeof(Stone));

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


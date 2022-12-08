#define _CRT_SECURE_NO_WARNINGS
#include"conio2.h"
#include"board.h"
#include"board_size.h"
#include"mystring.h"
#include"myvector.h"
#include<stdio.h>
#include<stdlib.h>


/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */




int main() {
	int zn = 0, x, y, attr = 7, back = 0, zero = 0, board_size = 0,
		board_x_location = 40, board_y_location = 2;
	x = board_x_location + 2;
	y = board_y_location + 1;
	char txt[32];
	bool new_game = false, next_round = false, handicap = false;

	Board board(board_size, board_x_location, board_y_location, 0, 0, true);

	textcolor(BLACK);
	textbackground(YELLOW);
	//static Board board(board_size, map_x_location, map_y_location);
	// if the program is compiled in pure C, then we need to initialize
	// the library ourselves; __cplusplus is defined only if a C++ compiler
	// is used
#ifndef __cplusplus
	Conio2_Init();
#endif
	// settitle sets the window title
	settitle("GO");
	// hide the blinking cursor
	_setcursortype(_NOCURSOR);
	do {
		int legend_x = 2, legend_y = 2;
		// we set black to be the background color
		// check conio2.h for available colors
		
		// clear the screen: we fill it out with spaces with
		// the specified background color
		clrscr();
		// we set the text color (7 == LIGHTGRAY)
		
		// we move the coursor to column 48 and row 1
		// rows and column are numbered starting with 1
		gotoxy(legend_x, legend_y++);
		// we print out a text at a given cursor position
		// the cursor will move by the length of the text
		cputs("Artur Binczyk 193138");
		gotoxy(legend_x, legend_y++);
		cputs("n       = new game");
		gotoxy(legend_x, legend_y++);
		cputs("q       = exit");
		gotoxy(legend_x, legend_y++);
		cputs("s       = save");
		gotoxy(legend_x, legend_y++);
		cputs("l       = load");
		gotoxy(legend_x, legend_y++);
		cputs("cursors = moving");
		gotoxy(legend_x, legend_y++);
		cputs("space   = change color");
		gotoxy(legend_x, legend_y++);
		cputs("enter   = change background color");
		// print out the code of the last key pressed
		if (zero) sprintf(txt, "key code: 0x00 0x%02x", zn);
		else sprintf(txt, "key code: 0x%02x", zn);
		gotoxy(legend_x, legend_y++);
		cputs(txt);
		gotoxy(legend_x, legend_y++);

		char cords[32];
		int cursor_on_board_x, cursor_on_board_y;
		cursor_on_board_x = x - board_x_location - 1;
		cursor_on_board_x /= 2;
		cursor_on_board_y = y - board_y_location - 1;

		

		
		if (new_game)
		{
			board_size = ChooseBoardSize(legend_x, legend_y);
			gotoxy(x, y);
			board.Draw(board_size);
			board.black_score = 0;
			board.white_score = 6.5;
			board.black_turn = true;
			new_game = false;
			next_round = true;
			handicap = Handicap(legend_x, legend_y);
			x = board_x_location + 2;
			y = board_y_location + 1;
		}
		else if (next_round)
		{
			cputs("1   = add stone");
			board.DisplayBoard();
			gotoxy(legend_x, legend_y++);
			char s_black[32];
			sprintf(s_black, "Black result: %.1f", board.black_score);
			puts(s_black);
			gotoxy(legend_x, legend_y++);
			char s_white[32];
			sprintf(s_white, "White result: %.1f", board.white_score);
			puts(s_white);
			gotoxy(legend_x, legend_y++);
			if (handicap)
			{
				cputs("h      = stop handicap");
				gotoxy(legend_x, legend_y++);
			}
			sprintf(cords, "coordinates: %d x %d ", (cursor_on_board_x), (cursor_on_board_y));
			puts(cords);
			gotoxy(legend_x, legend_y++);
		}
		

		gotoxy(x, y);
		putch('*');
		
		

		// we wait for key press and get its code
		// most key codes correspond to the characters, like
		// a is 'a', 2 is '2', + is '+', but some special keys
		// like cursors provide two characters, where the first
		// one is zero, e.g., "up arrow" is zero and 'H'
		
		zero = 0;
		zn = getch();
		// we do not want the key 'H' to play role of "up arrow"
		// so we check if the first code is zero
		if (zn == 0) {
			zero = 1;		// if this is the case then we read
			zn = getch();		// the next code knowing that this
			if (zn == 0x48)
			{
				if(cursor_on_board_y > 0)
					y--;
			}
			else if (zn == 0x50)
			{
				if(cursor_on_board_y < board_size - 1)
					y++;
			}
			else if (zn == 0x4b)
			{
				if(cursor_on_board_x > 0)
					x -= 2;
			}
			else if (zn == 0x4d)
			{
				if(cursor_on_board_x < board_size - 1)
					x += 2;
			}
		}
		else if (zn == 'n') 
		{
			if (ActionConfirm(legend_x, legend_y))
			{
				new_game = true;
				next_round = false;
			}
		}
		else if (zn == ' ') attr = (attr + 1) % 16;
		else if (zn == 0x0d) back = (back + 1) % 16;
		else if (zn == '1' && handicap == false) 
		{
			if (ActionConfirm(legend_x, legend_y))
			{
				board.AddStone(cursor_on_board_x, cursor_on_board_y);
				// enter key is 0x0d or '\r'
			}
		}
		else if (zn == '1' && handicap == true)
		{
			if (ActionConfirm(legend_x, legend_y))
			{
				board.AddStoneHandicap(cursor_on_board_x, cursor_on_board_y);
			}
		}
		else if (zn == 's')
		{
			if (ActionConfirm(legend_x, legend_y))
			{
				board.Save(&legend_x, &legend_y, x, y);
			}
		}
		else if (zn == 'l')
		{
			if (ActionConfirm(legend_x, legend_y))
			{
				board.Load(&legend_x, &legend_y, x, y);
				handicap = false;
				x = board_x_location + 2;
				y = board_y_location + 1;
			}
		}
		else if (zn == 'h')
		{
			if (ActionConfirm(legend_x, legend_y))
			{
				handicap = false;
				board.black_turn = false;
			}
		}
	} while (zn != 'q');

	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
	// visible after the program ends

	return 0;
}

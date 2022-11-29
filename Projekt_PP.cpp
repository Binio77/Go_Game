#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"conio2.h"
#include"board.h"
#include"board_size.h"

/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */




int main() {
	int zn = 0, x = 40, y = 12, attr = 7, back = 0, zero = 0, board_size = 0,
		board_x_location = 0, board_y_location = 0;
	char txt[32];
	bool has_chosen_board_size = false;
	bool board_was_once_drown = false;
	Board board(board_size, board_x_location, board_y_location);
	//static Board board(board_size, map_x_location, map_y_location);
	// if the program is compiled in pure C, then we need to initialize
	// the library ourselves; __cplusplus is defined only if a C++ compiler
	// is used
#ifndef __cplusplus
	Conio2_Init();
#endif
	// settitle sets the window title
	settitle("Artur, Binczyk, 193138");
	// hide the blinking cursor
	_setcursortype(_NOCURSOR);
	do {
		// we set black to be the background color
		// check conio2.h for available colors
		textbackground(YELLOW);
		// clear the screen: we fill it out with spaces with
		// the specified background color
		clrscr();
		// we set the text color (7 == LIGHTGRAY)
		textcolor(BLACK);
		// we move the coursor to column 48 and row 1
		// rows and column are numbered starting with 1
		gotoxy(2, 2);
		// we print out a text at a given cursor position
		// the cursor will move by the length of the text
		cputs("q       = exit");
		gotoxy(2, 3);
		cputs("cursors = moving");
		gotoxy(2, 4);
		cputs("space   = change color");
		gotoxy(2, 5);
		cputs("enter   = change background color");
		// print out the code of the last key pressed
		if (zero) sprintf(txt, "key code: 0x00 0x%02x", zn);
		else sprintf(txt, "key code: 0x%02x", zn);
		gotoxy(2, 6);
		cputs(txt);
		
		if (!has_chosen_board_size)
		{
			board_size = ChooseBoardSize();
			has_chosen_board_size = true;
		}
		gotoxy(50, 2);
		if (!board_was_once_drown)
		{
			board_x_location = wherex();
			board_y_location = wherey();
			board_was_once_drown = true;
		}
		// we draw a star
		gotoxy(x, y);
		textcolor(attr);
		textbackground(back);
		// putch prints one character and moves the cursor to the right
		board.Draw(board_size, board_x_location, board_y_location);
		gotoxy(x, y);
		putch('*');
		
		//printf("%i %i", map_x_location, map_y_location);
		

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
			if (zn == 0x48) y--;	// will be a special key
			else if (zn == 0x50) y++;
			else if (zn == 0x4b) x-=2;
			else if (zn == 0x4d) x+=2;
		}
		else if (zn == ' ') attr = (attr + 1) % 16;
		else if (zn == 0x0d) back = (back + 1) % 16;	// enter key is 0x0d or '\r'
	} while (zn != 'q');

	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
	// visible after the program ends
	//board.Delete();
	board.Delete();
	return 0;
}

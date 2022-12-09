#define _CRT_SECURE_NO_WARNINGS
#include"conio2.h"
#include"board.h"
#include"functions.h"
#include"mystring.h"
#include<stdio.h>
#include<stdlib.h>

#define BOARD_X_LOCATION 40
#define BOARD_Y_LOCATION 2
#define LENGHT_OF_LEGEND_OUTPUT 32
#define LEGEND_X_LOCATION 2
#define LEGEND_Y_LOCATION 2
/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */




int main() {
	int zn = 0, x, y, zero = 0, board_size = 0, board_x_movement = 0, board_y_movement = 0;
	x = BOARD_X_LOCATION + 2;
	y = BOARD_Y_LOCATION + 1;
	bool new_game = false, next_round = false, handicap = false, finish = false;

	Board board(board_size, BOARD_X_LOCATION, BOARD_Y_LOCATION, 0, 0, true, false);

	textcolor(BLACK);
	textbackground(YELLOW);

#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("GO");
	_setcursortype(_NOCURSOR);
	do {
		clrscr();
		int legend_x = LEGEND_X_LOCATION, legend_y = LEGEND_Y_LOCATION;
		gotoxy(legend_x, legend_y++);
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
		cputs("arrows = moving");
		gotoxy(legend_x, legend_y++);
		cputs("f       = finish");
		gotoxy(legend_x, legend_y++);

		char cords[32];
		int location_of_cursor_on_board_x, location_of_cursor_on_board_y;
		location_of_cursor_on_board_x = x - BOARD_X_LOCATION - 1;
		location_of_cursor_on_board_x /= 2;
		location_of_cursor_on_board_y = y - BOARD_Y_LOCATION - 1;

		text_info info;
		gettextinfo(&info);
		

		if (new_game)
		{
			board_size = ChooseBoardSize(legend_x, legend_y);
			board_x_movement = 0;
			board_y_movement = 0;
			board.bigger_than_screen = false;
			gotoxy(x, y);
			board.Draw(board_size);
			board.black_score = 0;
			board.white_score = 6.5;
			board.black_turn = true;
			new_game = false;
			next_round = true;
			handicap = Handicap(legend_x, legend_y);
			x = BOARD_X_LOCATION + 2;
			y = BOARD_Y_LOCATION + 1;
		}
		else if (next_round)
		{
			if (board.black_turn)
				Copy(board.plane, board.plane_bef_black_move, board.board_size);
			else
				Copy(board.plane, board.plane_bef_white_move, board.board_size);

			cputs("1   = add stone");
			if (info.screenwidth > (board.board_size + BOARD_X_LOCATION) && info.screenheight > (board.board_size + BOARD_Y_LOCATION))
			{
				board.DisplayBoard();
			}
			else
			{
				board.bigger_than_screen = true;
				board.Display_if_too_big(board_x_movement, board_y_movement);
			}
			gotoxy(legend_x, legend_y++);
			char s_black[LENGHT_OF_LEGEND_OUTPUT];
			sprintf(s_black, "Black result: %.1f", board.black_score);
			puts(s_black);
			gotoxy(legend_x, legend_y++);
			char s_white[LENGHT_OF_LEGEND_OUTPUT];
			sprintf(s_white, "White result: %.1f", board.white_score);
			puts(s_white);
			gotoxy(legend_x, legend_y++);
			if (handicap)
			{
				cputs("h      = stop handicap");
				gotoxy(legend_x, legend_y++);
			}
			sprintf(cords, "coordinates: %d x %d ", (location_of_cursor_on_board_x + board_x_movement), (location_of_cursor_on_board_y + board_y_movement));
			puts(cords);
			gotoxy(legend_x, legend_y++);
		}
		else if (finish)
		{
			char s_black[LENGHT_OF_LEGEND_OUTPUT];
			sprintf(s_black, "Black result: %.1f", board.black_score);
			puts(s_black);
			gotoxy(legend_x, legend_y++);
			char s_white[LENGHT_OF_LEGEND_OUTPUT];
			sprintf(s_white, "White result: %.1f", board.white_score);
			puts(s_white);
			gotoxy(legend_x, legend_y++);

			if (board.black_score > board.white_score)
				cputs("Black won");
			else
				cputs("White won");

			if (board.bigger_than_screen)
				board.Display_if_too_big(board_x_movement, board_y_movement);
			else
				board.DisplayBoard();
		}

		
		gotoxy(x, y);
		putch('*');
		
		zero = 0;
		zn = getch();

		if (zn == 0) {
			zero = 1;		
			zn = getch();		
			if (zn == 0x48)
			{
				if (location_of_cursor_on_board_y > 0)
				{
					y--;
				}
				else if (board.bigger_than_screen)
				{
					if (board_y_movement > 0)
						board_y_movement--;
				}
			}
			else if (zn == 0x50)
			{
				if (board.bigger_than_screen == false)
				{
					if (location_of_cursor_on_board_y < board.board_size - 1)
					{
						y++;
					}
				}
				else
				{
					if (location_of_cursor_on_board_y < 8)
					{
						y++;
					}
					else
					{
						if (board_y_movement < board.board_size - 9)
							board_y_movement++;
					}
				}
			}
			else if (zn == 0x4b)
			{
				if (location_of_cursor_on_board_x > 0)
				{
					x -= 2;
				}
				else if (board.bigger_than_screen)
				{
					if (board_x_movement > 0)
						board_x_movement--;
				}

			}
			else if (zn == 0x4d)
			{
				if (board.bigger_than_screen == false)
				{
					if (location_of_cursor_on_board_x < board.board_size - 1)
					{
						x += 2;
					}
				}
				else
				{
					if (location_of_cursor_on_board_x < 8)
					{
						x += 2;
					}
					else
					{
						if (board_x_movement < board.board_size - 9)
							board_x_movement++;
					}
				}
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
		else if (zn == '1' && handicap == false) 
		{
			if (ActionConfirm(legend_x, legend_y))
			{
				board.AddStone(location_of_cursor_on_board_x + board_x_movement, location_of_cursor_on_board_y + board_y_movement);
			}
		}
		else if (zn == '1' && handicap == true)
		{
			if (ActionConfirm(legend_x, legend_y))
			{
				board.AddStoneHandicap(location_of_cursor_on_board_x, location_of_cursor_on_board_y);
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
				board.Load(&legend_x, &legend_y, x, y, &board_x_movement, &board_y_movement);
				handicap = false;
				x = BOARD_X_LOCATION + 2;
				y = BOARD_Y_LOCATION + 1;
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
		else if (zn == 'f')
		{
			if (ActionConfirm(legend_x, legend_y))
			{
				board.Finish();
				next_round = false;
				finish = true;
			}
		}
	} while (zn != 'q');

	_setcursortype(_NORMALCURSOR);

	return 0;
}

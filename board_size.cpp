#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"conio2.h"
#include<cstdbool>;
#include"board_size.h"

int ChooseBoardSize() {
	textbackground(YELLOW);
	textcolor(BLACK);
	gotoxy(2, 7);
	cputs("board size 9x9 press 1");
	gotoxy(2, 8);
	cputs("board size 13x13 press 2");
	gotoxy(2, 9);
	cputs("board size 19x19 press 3");
	gotoxy(2, 10);
	cputs("board size of your choice press 4");
	gotoxy(2, 11);

	char choice_of_board_size = getch();
	switch (choice_of_board_size)
	{
	case '1':
	{
		return 9;
	}
	case '2':
	{
		return 13;
	}
	case '3':
	{
		return 19;
	}
	case '4':
	{
		gotoxy(2, 12);
		cputs("choose write your own size ");
		char current_char_number;
		int sum = 0;
		int i = 1;

		do {
			current_char_number = getche();
			if (current_char_number >= '1' && current_char_number <= '9')
			{


			}
		} while (current_char_number >= '1' && current_char_number <= '9');

		return sum;
	}
	default:
	{
		break;
	}
	}
	return 0;
}
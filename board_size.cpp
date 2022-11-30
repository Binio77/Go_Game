#include"board_size.h"
#include"mystring.h"
#include"conio2.h"
#include<stdio.h>
#include<stdlib.h>
#include<cstdbool>;


int ChooseBoardSize(int _legend_x, int _legend_y) {
	textbackground(YELLOW);
	textcolor(BLACK);
	gotoxy(_legend_x, _legend_y++);
	cputs("board size 9x9 press 2");
	gotoxy(_legend_x, _legend_y++);
	cputs("board size 13x13 press 3");
	gotoxy(_legend_x, _legend_y++);
	cputs("board size 19x19 press 4");
	gotoxy(_legend_x, _legend_y++);
	cputs("board size of your choice press 5");
	gotoxy(_legend_x, _legend_y++);

	char choice_of_board_size = getch();
	switch (choice_of_board_size)
	{
	case '2':
	{
		return 9;
	}
	case '3':
	{
		return 13;
	}
	case '4':
	{
		return 19;
	}
	case '5':
	{
		gotoxy(2, 12);
		gotoxy(_legend_x, _legend_y++);
		cputs("choose write your own size ");
		char current_char_digit;
		MyString number_string;
		int sum = 0;
		int multiplier = 1;
		gotoxy(_legend_x, _legend_y++);
		do {
			current_char_digit = getche();
			if (current_char_digit >= '0' && current_char_digit <= '9')
			{
				number_string.AddLetter(current_char_digit);
			}
		} while (current_char_digit >= '0' && current_char_digit <= '9');
		
		for (int i = number_string.my_string_size - 1; i >= 0; i--)
		{
			sum += (*(number_string.mystring + i) - '0') * multiplier;
			multiplier *= 10;
		}
		
		return sum;
	}
	default:
	{
		break;
	}
	}
	return 0;
}
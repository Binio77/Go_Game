#pragma warning(disable:4996)
#include"board.h"
#include"stone.h"
#include"conio2.h"
#include"mystring.h"
#include<stdio.h>
#include<stdlib.h>
#include<cstdbool>



Board::~Board()
{
	delete(plane);
}


Board::Board(int _board_size, int _start_cursorx, int _start_cursor_y, double _black_score, double _white_score, bool _black_turn) : board_size(_board_size), start_cursor_x(_start_cursorx),
	start_cursor_y(_start_cursor_y), black_score(_black_score), white_score(_white_score), black_turn(_black_turn)
{
	plane = new Stone[board_size * board_size];
}



Board::Board() : board_size(0), start_cursor_x(0), start_cursor_y(0), plane(nullptr), black_score(0.0), white_score(0.0), black_turn(true) {};

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
			{
				if ((plane + y * board_size + x)->stone_colour)
					textcolor(BLACK);
				else
					textcolor(BLUE);
				putch('%');
				textcolor(BLACK);
			}

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
	delete(plane);
	plane = new Stone[board_size * board_size];
}

void Board::Draw(int _board_size)
{
	board_size = _board_size;
	ChangeSize();
	FillBoard();
	DisplayBoard();
}

void Board::AddStone(int _current_x, int _current_y)
{
	bool black_color;
	bool deleted = false;
	if ((plane + _current_y * board_size + _current_x)->stone_is_here == false)
	{
		if (black_turn)
		{
			(plane + _current_y * board_size + _current_x)->stone_colour = true;
			black_color = true;
			black_turn = false;
		}
		else
		{
			(plane + _current_y * board_size + _current_x)->stone_colour = false;
			black_color = false;
			black_turn = true;
		}

		(plane + _current_y * board_size + _current_x)->stone_is_here = true;

		if (_current_x > 0 && (plane + _current_y * board_size + _current_x - 1)->stone_is_here == true && (plane + _current_y * board_size + _current_x - 1)->stone_colour != black_color)
			Check(_current_x - 1, _current_y, &deleted);

		if (_current_x < board_size - 1 && (plane + _current_y * board_size + _current_x + 1)->stone_is_here == true && (plane + _current_y * board_size + _current_x + 1)->stone_colour != black_color)
			Check(_current_x + 1, _current_y, &deleted);

		if (_current_y > 0 && (plane + (_current_y - 1) * board_size + _current_x)->stone_is_here == true && (plane + (_current_y - 1) * board_size + _current_x)->stone_colour != black_color)
			Check(_current_x, _current_y - 1, &deleted);

		if (_current_y < board_size - 1 && (plane + (_current_y + 1) * board_size + _current_x)->stone_is_here == true && (plane + (_current_y + 1) * board_size + _current_x)->stone_colour != black_color)
			Check(_current_x, _current_y + 1, &deleted);

		if (!deleted)
		{
			bool stone_can_be_here = DeleteStones(_current_x, _current_y, black_color, -3, -3);
			if (stone_can_be_here == false)
			{
				(plane + _current_y * board_size + _current_x)->stone_is_here = false;

				if (black_turn)
					black_turn = false;
				else
					black_turn = true;
			}
		}
		


	}
}
void Board::AddStoneHandicap(int _current_x, int _current_y)
{
	if ((plane + _current_y * board_size + _current_x)->stone_is_here == false)
	{
		(plane + _current_y * board_size + _current_x)->stone_colour = true;
		(plane + _current_y * board_size + _current_x)->stone_is_here = true;
		white_score += 0.5;
	}

}

void Board::Check(int _current_x, int _current_y, bool * _deleted)
{
	bool black_color = (plane + _current_y * board_size + _current_x)->stone_colour;
	ClearArray();
	bool stone_to_save = false;
	stone_to_save = DeleteStones(_current_x, _current_y, black_color, -3, -3);
	if (!stone_to_save)
	{
		for (int y = 0; y < board_size; y++)
		{
			for (int x = 0; x < board_size; x++)
			{
				if ((plane + y * board_size + x)->was_here == true)
				{
					(plane + y * board_size + x)->stone_is_here = false;
					if (black_color == false)
						black_score++;
					else
						white_score++;
				}
			}
		}
		*_deleted = true;
	}

	ClearArray();
}

bool Board::DeleteStones(int _current_x, int _current_y, bool black_color, int came_fr_x, int came_fr_y)
{

	int breathes = 4;
	(plane + _current_y * board_size + _current_x)->was_here = true;
	if (_current_x > 0 && (plane + _current_y * board_size + (_current_x -1))->was_here == false)
	{
		if((plane + _current_y * board_size + (_current_x - 1))->stone_is_here == true)
		{
			if ((plane + _current_y * board_size + (_current_x - 1))->stone_colour != black_color)
			{
				breathes--;
			}
			else
			{
				if (_current_x - 1 == came_fr_x || DeleteStones(_current_x - 1, _current_y, black_color, _current_x, _current_y) == false)
					breathes--;
			}
		}
	}
	else
	{
		breathes--;
	}

	if (_current_x < board_size - 1 && (plane + _current_y * board_size + (_current_x + 1))->was_here == false)
	{
		if ((plane + _current_y * board_size + (_current_x + 1))->stone_is_here == true)
		{
			if ((plane + _current_y * board_size + (_current_x + 1))->stone_colour != black_color)
			{
				breathes--;
			}
			else
			{
				if (_current_x + 1 == came_fr_x || DeleteStones(_current_x + 1, _current_y, black_color, _current_x, _current_y) == false)
					breathes--;
			}
		}
	}
	else
	{
		breathes--;
	}

	if (_current_y > 0 && (plane + (_current_y - 1) * board_size + _current_x)->was_here == false)
	{
		if ((plane + (_current_y - 1) * board_size + _current_x)->stone_is_here == true)
		{
			if ((plane + (_current_y - 1) * board_size + _current_x)->stone_colour != black_color)
			{
				breathes--;
			}
			else
			{
				if (_current_y - 1 == came_fr_y || DeleteStones(_current_x, _current_y - 1, black_color, _current_x, _current_y) == false)
					breathes--;
			}
		}
	}
	else
	{
		breathes--;
	}

	if (_current_y < board_size - 1 && (plane + (_current_y + 1) * board_size + _current_x)->was_here == false)
	{
		if ((plane + (_current_y + 1) * board_size + _current_x)->stone_is_here == true)
		{
			if ((plane + (_current_y + 1) * board_size + _current_x)->stone_colour != black_color)
			{
				breathes--;
			}
			else
			{
				if (_current_y + 1 == came_fr_y || DeleteStones(_current_x, _current_y + 1, black_color, _current_x, _current_y) == false)
					breathes--;
			}
		}
	}
	else
	{
		breathes--;
	}
	
	
	if (breathes == 0)
	{
		return false;
	}
	else
		return true;

}

void Board::ClearArray()
{
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size; x++)
		{
			(plane + y * board_size + x)->was_here = false;
		}
	}
}

void Board::Save(int *_legend_x, int *_legend_y, int _x, int _y)
{
	char file_name[30];
	*_legend_y += 4;
	gotoxy(*_legend_x, *_legend_y);
	cputs("Write name of file: ");

	SelectName(file_name);
	gotoxy(_x, _y);
	FILE* save;
	save = fopen(file_name, "w");
	fprintf(save, "%d %.1f %.1f %d ", board_size, black_score, white_score, black_turn);
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size; x++)
		{
			if ((plane + y * board_size + x)->stone_is_here == false)
			{
				fprintf(save, "%c", '+');
			}
			else if ((plane + y * board_size + x)->stone_colour == true)
			{
				fprintf(save, "%c", '1');
			}
			else
			{
				fprintf(save, "%c", '0');
			}
		}
	}
	fclose(save);
}

void Board::Load(int* _legend_x, int* _legend_y, int _x, int _y)
{
	char file_name[30];
	*_legend_y += 4;
	gotoxy(*_legend_x, *_legend_y);
	cputs("Write name of file: ");
	SelectName(file_name);
	gotoxy(_x, _y);
	FILE* load;
	load = fopen(file_name, "r");
	if (load == NULL)
	{
		gotoxy(*_legend_x, *_legend_y++);
		cputs("There is no file with this name");
		gotoxy(_x, _y);
		
	}
	else
	{
		bool turn;
		int size;
		float score;
		fscanf(load, "%d ", &size);
		board_size = size;
		delete(plane);
		plane = new Stone[board_size * board_size];
		fscanf(load, "%f ", &score);
		black_score = score;
		fscanf(load, "%f ", &score);
		white_score = score;
		fscanf(load, "&d ", &turn);
		black_turn = turn;

		char number;
		number = fgetc(load);
		number = fgetc(load);
		for (int y = 0; y < board_size; y++)
		{
			for (int x = 0; x < board_size; x++)
			{
				number = fgetc(load);
				if (number == '+')
				{
					(plane + y * board_size + x)->stone_is_here = false;
				}
				else if (number == '1')
				{
					(plane + y * board_size + x)->stone_is_here = true;
					(plane + y * board_size + x)->stone_colour = true;
				}
				else
				{
					(plane + y * board_size + x)->stone_is_here = true;
					(plane + y * board_size + x)->stone_colour = false;
				}
			}
		}
		fclose(load);
		
	}
}


void SelectName(char* name)
{
	char letter;
	int i = 0;
	do
	{
		letter = getche();
		if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= '0' && letter <= '9'))
		{
			name[i] = letter;
			i++;
		}
	} while ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= '0' && letter <= '9'));
	name[i] = '\0';
}

void ClearInputTable(char * number)
{
	for (int i = 0; i < 30; i++)
		number[i] = 0;

}



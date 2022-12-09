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
	delete(plane_bef_black_move);
	delete(plane_bef_white_move);
}


Board::Board(int _board_size, int _corner_x, int _corner_y, double _black_score, double _white_score, bool _black_turn, bool _bigger_than_screen) : 
	board_size(_board_size), corner_x(_corner_x),corner_y(_corner_y), black_score(_black_score), white_score(_white_score), black_turn(_black_turn), bigger_than_screen(_bigger_than_screen)
{
	plane = new Stone[board_size * board_size];
	plane_bef_black_move = new Stone[board_size * board_size];
	plane_bef_white_move = new Stone[board_size * board_size];
}



Board::Board() : board_size(0), corner_x(0), corner_y(0), plane(nullptr), black_score(0.0), white_score(0.0), 
	black_turn(true), bigger_than_screen(false) {};

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
	int current_cursor_x = corner_x, current_cursor_y = corner_y;
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
				putch('#');
				textcolor(BLACK);
			}

			putch(' ');

		}
		putch('|');
		current_cursor_x = corner_x;
		gotoxy(current_cursor_x, ++current_cursor_y);
	}
	current_cursor_x = corner_x;
	gotoxy(current_cursor_x, current_cursor_y++);
	cputs("+");
	for (int x = 0; x < board_size * 2 + 1; x++)
	{
		putch('-');
	}
	putch('+');
	
}

void Board::Display_if_too_big(int array_x, int array_y)
{
	int current_cursor_x = corner_x, current_cursor_y = corner_y;
	gotoxy(current_cursor_x, current_cursor_y);
	cputs("+");
	for (int x = 0; x < 19; x++)
	{
		putch('-');
	}
	putch('+');
	gotoxy(current_cursor_x, ++current_cursor_y);
	for (int y = array_y; y < 9 + array_y; y++)
	{
		cputs("| ");
		for (int x = array_x; x < 9 + array_x; x++)
		{
			if ((plane + y * board_size + x)->stone_is_here == false)
				putch('+');
			else
			{
				if ((plane + y * board_size + x)->stone_colour)
					textcolor(BLACK);
				else
					textcolor(BLUE);
				putch('#');
				textcolor(BLACK);
			}

			putch(' ');
		}
		putch('|');
		current_cursor_x = corner_x;
		gotoxy(current_cursor_x, ++current_cursor_y);
	}
	current_cursor_x = corner_x;
	gotoxy(current_cursor_x, current_cursor_y++);
	cputs("+");
	for (int x = 0; x < 19; x++)
	{
		putch('-');
	}
	putch('+');
}


void Board::ChangeSize()
{
	delete(plane);
	delete(plane_bef_black_move);
	delete(plane_bef_white_move);
	plane = new Stone[board_size * board_size];
	plane_bef_black_move = new Stone[board_size * board_size];
	plane_bef_white_move = new Stone[board_size * board_size];
}

void Board::Draw(int _board_size)
{
	board_size = _board_size;
	ChangeSize();
	FillBoard();
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
			CheckStone(_current_x - 1, _current_y, &deleted);

		if (_current_x < board_size - 1 && (plane + _current_y * board_size + _current_x + 1)->stone_is_here == true && (plane + _current_y * board_size + _current_x + 1)->stone_colour != black_color)
			CheckStone(_current_x + 1, _current_y, &deleted);

		if (_current_y > 0 && (plane + (_current_y - 1) * board_size + _current_x)->stone_is_here == true && (plane + (_current_y - 1) * board_size + _current_x)->stone_colour != black_color)
			CheckStone(_current_x, _current_y - 1, &deleted);

		if (_current_y < board_size - 1 && (plane + (_current_y + 1) * board_size + _current_x)->stone_is_here == true && (plane + (_current_y + 1) * board_size + _current_x)->stone_colour != black_color)
			CheckStone(_current_x, _current_y + 1, &deleted);

		if (!deleted)
		{
			bool stone_can_be_here = DeleteStones(_current_x, _current_y, black_color);
			if (stone_can_be_here == false)
			{
				(plane + _current_y * board_size + _current_x)->stone_is_here = false;

				if (black_turn)
					black_turn = false;
				else
					black_turn = true;
			}
		}
		else
		{
			if (black_color)
			{
				if (Compare(plane, plane_bef_white_move, board_size))
				{
					Copy(plane_bef_black_move, plane, board_size);
					black_turn = black_color;
					black_score--;
				}
			}
			else if(!black_color)
			{
				if (Compare(plane, plane_bef_black_move, board_size))
				{
					Copy(plane_bef_white_move, plane, board_size);
					black_turn = black_color;
					white_score--;
				}
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

void Board::CheckStone(int _current_x, int _current_y, bool * _deleted)
{
	bool black_color = (plane + _current_y * board_size + _current_x)->stone_colour;
	ClearArray();
	bool stone_to_save = false;
	stone_to_save = DeleteStones(_current_x, _current_y, black_color);
	if (!stone_to_save)
	{
		for (int y = 0; y < board_size; y++)
		{
			for (int x = 0; x < board_size; x++)
			{
				if ((plane + y * board_size + x)->was_here == true)
				{
					(plane + y * board_size + x)->stone_is_here = false;
					(plane + y * board_size + x)->stone_colour = false;
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

bool Board::DeleteStones(int _current_x, int _current_y, bool black_color)
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
				if (DeleteStones(_current_x - 1, _current_y, black_color) == false)
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
				if (DeleteStones(_current_x + 1, _current_y, black_color) == false)
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
				if (DeleteStones(_current_x, _current_y - 1, black_color) == false)
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
				if (DeleteStones(_current_x, _current_y + 1, black_color) == false)
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
	fprintf(save, "%d %.1f %.1f %d %d ", board_size, black_score, white_score, black_turn, bigger_than_screen);
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
	fprintf(save, "%c", ' ');
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size; x++)
		{
			if ((plane_bef_black_move + y * board_size + x)->stone_is_here == false)
			{
				fprintf(save, "%c", '+');
			}
			else if ((plane_bef_black_move + y * board_size + x)->stone_colour == true)
			{
				fprintf(save, "%c", '1');
			}
			else
			{
				fprintf(save, "%c", '0');
			}
		}
	}
	fprintf(save, "%c", ' ');
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size; x++)
		{
			if ((plane_bef_white_move + y * board_size + x)->stone_is_here == false)
			{
				fprintf(save, "%c", '+');
			}
			else if ((plane_bef_white_move + y * board_size + x)->stone_colour == true)
			{
				fprintf(save, "%c", '1');
			}
			else
			{
				fprintf(save, "%c", '0');
			}
		}
	}
	fprintf(save, "%c", ' ');

	fclose(save);
}

void Board::Load(int* _legend_x, int* _legend_y, int _x, int _y, int *_board_x_movement, int *_board_y_movement)
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
		cputs("There is no file with this name press anything to continue");
		getch();
		gotoxy(_x, _y);
		
	}
	else
	{
		char symbol_read;
		int size;
		float score;

		fscanf(load, "%d", &size);
		board_size = size;
		delete(plane);
		delete(plane_bef_black_move);
		delete(plane_bef_white_move);
		plane = new Stone[board_size * board_size];
		plane_bef_black_move = new Stone[board_size * board_size];
		plane_bef_white_move = new Stone[board_size * board_size];
		*_board_x_movement = 0;
		*_board_y_movement = 0;
		fscanf(load, "%f", &score);
		black_score = score;
		fscanf(load, "%f", &score);
		white_score = score;
		symbol_read = fgetc(load);
		fscanf(load, "%c", &symbol_read);

		if (symbol_read == '1')
			black_turn = true;
		else
			black_turn = false;

		symbol_read = fgetc(load);
		fscanf(load, "%c", &symbol_read);

		if (symbol_read == '1')
			bigger_than_screen = true;
		else
			bigger_than_screen = false;

		symbol_read = fgetc(load);



		for (int y = 0; y < board_size; y++)
		{
			for (int x = 0; x < board_size; x++)
			{
				symbol_read = fgetc(load);
				ReadToArray(plane, symbol_read, x, y);
			}
		}
		symbol_read = fgetc(load);
		for (int y = 0; y < board_size; y++)
		{
			for (int x = 0; x < board_size; x++)
			{
				
				symbol_read = fgetc(load);
				ReadToArray(plane_bef_black_move, symbol_read, x, y);
			}
		}
		symbol_read = fgetc(load);
		for (int y = 0; y < board_size; y++)
		{
			for (int x = 0; x < board_size; x++)
			{
				symbol_read = fgetc(load);
				ReadToArray(plane_bef_white_move, symbol_read, x, y);
			}
		}
		fclose(load);
		
	}
}

void Board::ReadToArray(Stone* plane, char number, int x, int y)
{
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

void Board::Finish()
{
	ClearArray();
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size; x++)
		{
			int points_to_add = 0;
			if ((plane + y * board_size + x) ->stone_is_here == false && (plane + y * board_size + x)->was_here == false)
			{
				int result = PointsCount(x, y, &points_to_add);
				if (result == 1)
				{
					black_score += points_to_add;
				}
				else if (result == -1)
				{
					white_score += points_to_add;
				}
			}
		}
	}
	ClearArray();
}

int Board::PointsCount(int _current_x, int _current_y, int *_points_to_add)
{
	int count_of_white = 0, count_of_black = 0, count_of_no_mans_land = 0, result;
	(plane + _current_y * board_size + _current_x)->was_here = true;
	if (_current_x > 0 && (plane + _current_y * board_size + (_current_x - 1))->was_here == false)
	{
		if ((plane + _current_y * board_size + (_current_x - 1))->stone_is_here == false)
		{
			result = PointsCount(_current_x - 1, _current_y, _points_to_add);
			if (result == 0)
			{
				count_of_no_mans_land++;
			}
			else if (result == 1)
			{
				count_of_black++;
			}
			else if(result == 1)
			{
				count_of_white++;
			}
		}
		else if ((plane + _current_y * board_size + (_current_x - 1))->stone_colour == true)
		{
			count_of_black++;
		}
		else if ((plane + _current_y * board_size + (_current_x - 1))->stone_colour == false)
		{
			count_of_white++;
		}
	}

	if (_current_x < board_size - 1 && (plane + _current_y * board_size + (_current_x + 1))->was_here == false)
	{
		if ((plane + _current_y * board_size + (_current_x + 1))->stone_is_here == false)
		{
			result = PointsCount(_current_x + 1, _current_y, _points_to_add);
			if (result == 0)
			{
				count_of_no_mans_land++;
			}
			else if (result == 1)
			{
				count_of_black++;
			}
			else if (result == 1)
			{
				count_of_white++;
			}

		}
		else if ((plane + _current_y * board_size + (_current_x + 1))->stone_colour == true)
		{
			count_of_black++;
		}
		else if ((plane + _current_y * board_size + (_current_x + 1))->stone_colour == false)
		{
			count_of_white++;
		}
	}

	if (_current_y > 0 && (plane + (_current_y - 1) * board_size + _current_x)->was_here == false)
	{
		if ((plane + (_current_y - 1) * board_size + _current_x)->stone_is_here == false)
		{
			result = PointsCount(_current_x, _current_y - 1, _points_to_add);
			if (result == 0)
			{
				count_of_no_mans_land++;
			}
			else if (result == 1)
			{
				count_of_black++;
			}
			else if (result == 1)
			{
				count_of_white++;
			}
		}
		else if ((plane + (_current_y - 1) * board_size + _current_x)->stone_colour == true)
		{
			count_of_black++;
		}
		else if ((plane + (_current_y - 1) * board_size + _current_x)->stone_colour == false)
		{
			count_of_white++;
		}
	}

	if (_current_y < board_size - 1 && (plane + (_current_y + 1) * board_size + _current_x)->was_here == false)
	{
		if ((plane + (_current_y + 1) * board_size + _current_x)->stone_is_here == false)
		{
			result = PointsCount(_current_x, _current_y + 1, _points_to_add);
			if (result == 0)
			{
				count_of_no_mans_land++;
			}
			else if (result == 1)
			{
				count_of_black++;
			}
			else if (result == 1)
			{
				count_of_white++;
			}
		}
		else if ((plane + (_current_y + 1) * board_size + _current_x)->stone_colour == true)
		{
			count_of_black++;
		}
		else if ((plane + (_current_y + 1) * board_size + _current_x)->stone_colour == false)
		{
			count_of_white++;
		}
	}
	*_points_to_add += 1;
	if (count_of_no_mans_land > 0 || (count_of_black > 0 && count_of_white > 0))
		return 0;
	else if (count_of_black > 0)
		return 1;
	else if (count_of_white > 0)
		return -1;
	else
		return 2;

}


void Copy(Stone* source, Stone* destination, int _board_size)
{
	for (int y = 0; y < _board_size; y++)
	{
		for (int x = 0; x < _board_size; x++)
		{
			(destination + y * _board_size + x)->stone_is_here = (source + y * _board_size + x)->stone_is_here;
			(destination + y * _board_size + x)->stone_colour = (source + y * _board_size + x)->stone_colour;
			(destination + y * _board_size + x)->was_here = (source + y * _board_size + x)->was_here;
		}
	}
}
bool Compare(Stone* plane1, Stone* plane2, int _board_size)
{
	for (int y = 0; y < _board_size; y++)
	{
		for (int x = 0; x < _board_size; x++)
		{
			bool a = (plane1 + y * _board_size + x)->stone_is_here;
			bool b = (plane2 + y * _board_size + x)->stone_is_here;
			bool c = (plane1 + y * _board_size + x)->stone_colour;
			bool d = (plane2 + y * _board_size + x)->stone_colour;
			if ((plane1 + y * _board_size + x)->stone_is_here != ((plane2 + y * _board_size + x)->stone_is_here))
				return false;

			if ((plane1 + y * _board_size + x)->stone_colour != ((plane2 + y * _board_size + x)->stone_colour))
				return false;
		}
	}
	return true;
}

void SelectName(char* name)
{
	char letter;
	int counter = 0;
	do
	{
		letter = getche();
		if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= '0' && letter <= '9'))
		{
			name[counter] = letter;
			counter++;
		}
	} while ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= '0' && letter <= '9'));
	name[counter] = '\0';
}



#ifndef board_h
#define board_h
#include"stone.h"
class Board
{
public:
	int board_size, start_cursor_x, start_cursor_y;
	Stone *plane;

	Board(int, int, int);
	Board();
	virtual ~Board();
	void Draw(int, int, int);
	void FillBoard();
	void DisplayBoard();
	void ChangeSize();

};
#endif
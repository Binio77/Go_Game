#ifndef board_h
#define board_h
#include"stone.h"
#include"myvector.h"
class Board
{
public:
	int board_size, start_cursor_x, start_cursor_y;
	Stone *plane;
	double black_score, white_score;
	bool black_turn;

	Board(int, int, int, double, double, bool);
	Board();
	virtual ~Board();
	void Draw(int);
	void FillBoard();
	void DisplayBoard();
	void ChangeSize();
	void AddStone(int, int);
	bool DeleteStones(int, int, bool, int, int);
	void Check(int, int, bool*);
	void ClearArray();
	void Save(int *, int *, int, int);
	void Load(int *, int*, int, int);
	void AddStoneHandicap(int, int);
	
};
void SelectName(char*);
void ClearInputTable(char*);
#endif
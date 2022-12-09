#ifndef board_h
#define board_h
#include"stone.h"
class Board
{
public:
	int board_size, corner_x, corner_y;
	Stone *plane, *plane_bef_black_move, *plane_bef_white_move;
	double black_score, white_score;
	bool black_turn, bigger_than_screen;

	Board(int, int, int, double, double, bool, bool);
	Board();
	virtual ~Board();
	void Draw(int);
	void FillBoard();
	void DisplayBoard();
	void Display_if_too_big(int, int);
	void ChangeSize();
	void AddStone(int, int);
	void AddStoneHandicap(int, int);
	bool DeleteStones(int, int, bool);
	void CheckStone(int, int, bool*);
	void ClearArray();
	void Save(int *, int *, int, int);
	void Load(int *, int*, int, int, int*, int*);
	void ReadToArray(Stone*, char, int, int);
	void Finish();
	int PointsCount(int, int, int *);
};
void Copy(Stone *, Stone *, int);
bool Compare(Stone*, Stone*, int);
void SelectName(char*);
#endif
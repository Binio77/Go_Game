class Board
{
public:
	int board_size, start_cursor_x, start_cursor_y;
	char* plane;
	//char** ptr_plane;

	Board(int, int, int);
	Board();
	void Draw(int, int, int);
	void FillBoard();
	void DisplayBoard();
	void Delete();
	void ChangeSize();

};
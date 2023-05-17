#include "TextureManager.h"
#include "Cell.h"
#include "Random.h"
#include <vector>
using std::vector;

class Board
{
private:
	int mines = 0;
	int flags = 0;
	vector<Cell> board;
	unsigned int columns;
	unsigned int rows;
	unsigned int mine_count;
	bool debug = false;
	bool gameOver = false;
	bool win = false;
public:
	// Constructor
	Board(unsigned int col, unsigned int row, unsigned int m);

	// Initial Methods
	void Initialize(int board_num);
	void InitializeRandom();

	// Getters
	Cell& GetCell(unsigned int cell_num);
	unsigned int GetColumns();
	unsigned int GetRows();
	unsigned int GetSize();
	bool GetGameOver();
	bool GetVictory();
	int GetFlagCount();
	int GetMineCount();

	// Setters
	void SetNextTo();
	void SetSurroundNumbers();

	// Modes
	void ShowHiddenState();
	void SetGameOver();
	void RevealCell(Cell* cell);
	void Flag(Cell* cell);
};
#include "Board.h"
#include "Extra.h"

Board::Board(unsigned int col, unsigned int row, unsigned int m) {
    columns = col;
    rows = row;
    mine_count = m;
}

Cell& Board::GetCell(unsigned int cell_num) {
    return board.at(cell_num);

}

unsigned int Board::GetColumns() {
    return columns;
}

unsigned int Board::GetRows() {
    return rows;
}

unsigned int Board::GetSize() {
    return columns * rows;
}

void Board::ShowHiddenState() {
    if (debug)
        debug = false;
    else
        debug = true;
    if (!gameOver && !win) {
        for (unsigned int i = 0; i < GetSize(); i++) {
            if (debug && board[i].getHiddenState() == Cell::HiddenState::MINE)
                board[i].SetSprite("mine");
            else if (!debug && board[i].getState() == Cell::State::FLAG)
                board[i].SetSprite("flag");
            else if (!debug && board[i].getHiddenState() == Cell::HiddenState::MINE)
                board[i].SetSprite("tile_hidden");
        }
    }
}

void Board::Initialize(int load_board) {

    // Used to load test Boards
    vector<char> mineLocal = Extra::readFile(load_board);
    gameOver = false;
    win = false;
    board.clear();
    mines = 0;
    flags = 0;

    
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++) {
            sf::Vector2f position = sf::Vector2f((float)(j) * 32, (float)(i) * 32);
            Cell::HiddenState state;
            unsigned int x = (columns * i) + j;
            if (mineLocal.at(x) == '1') {
                state = Cell::HiddenState::MINE;
                mines += 1;
            }
            else
                state = Cell::HiddenState::EMPTY;

            // Keep mines revealed if debug
            if (debug && state == Cell::HiddenState::MINE) {
                Cell newCell = Cell(position, "mine", state);
                board.push_back(newCell);
            }
            else {
                Cell newCell = Cell(position, "tile_hidden", state);
                board.push_back(newCell);
            }
        }
    }

    SetNextTo();
    SetSurroundNumbers();
}

void Board::InitializeRandom() {

    
    vector<int> mineLocal;
    mineLocal.push_back(Random::Int(0, rows * columns - 1));
    while (mineLocal.size() < mine_count) {
        int x = Random::Int(0, rows * columns - 1);
        bool dup = false;
        for (unsigned int i = 0; i < mineLocal.size(); i++) {
            if (x == mineLocal.at(i)) {
                dup = true;
                break;
            }
        }
        if (dup == false)
            mineLocal.push_back(x);
    }

   
    gameOver = false;
    win = false;
    board.clear();
    mines = 0;
    flags = 0;

    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++) {
            sf::Vector2f position = sf::Vector2f((float)(j) * 32, (float)(i) * 32);
            Cell::HiddenState state = Cell::HiddenState::EMPTY;
            Cell newCell = Cell(position, "tile_hidden", state);
            board.push_back(newCell);
        }
    }

    for (unsigned int i = 0; i < mineLocal.size(); i++) {
        board[mineLocal[i]].setHiddenState(Cell::HiddenState::MINE);
        mines += 1;
        if (debug)
            board[mineLocal[i]].SetSprite("mine");
    }

    
    SetNextTo();
    SetSurroundNumbers();
}

bool Board::GetGameOver() {
    return gameOver;
}

void Board::SetGameOver() {
    gameOver = true;

    
    for (unsigned int i = 0; i < board.size(); i++) {
        board[i].SetClickability(false);
        board[i].SetRightClickability(false);
        if (board[i].getHiddenState() == Cell::HiddenState::MINE) {
            board[i].SetSprite("mine");
        }
    }
}

void Board::SetNextTo() {
    for (unsigned int i = 0; i < board.size(); i++) {
        //Setting corner surrounding cells. 3 cells
        if (i == 0) {
            board[i].AddNextTo(&board[1]);
            board[i].AddNextTo(&board[columns]);
            board[i].AddNextTo(&board[columns + 1]);
        }
        else if (i == columns - 1) {
            board[i].AddNextTo(&board[i - 2]);
            board[i].AddNextTo(&board[i * 2]);
            board[i].AddNextTo(&board[(i * 2) + 1]);
        }
        else if (i == (columns * rows) - columns) {
            board[i].AddNextTo(&board[i - columns]);
            board[i].AddNextTo(&board[i - columns + 1]);
            board[i].AddNextTo(&board[i + 1]);
        }
        else if (i == (columns * rows) - 1) {
            board[i].AddNextTo(&board[i - columns]);
            board[i].AddNextTo(&board[i - columns - 1]);
            board[i].AddNextTo(&board[i - 1]);
        }

        // Surrounding cells on edges. Surround = 5 cells
        else if (i > 0 && i < columns - 1) {
            board[i].AddNextTo(&board[i - 1]);
            board[i].AddNextTo(&board[i + 1]);
            board[i].AddNextTo(&board[i + columns - 1]);
            board[i].AddNextTo(&board[i + columns]);
            board[i].AddNextTo(&board[i + columns + 1]);
        }
        else if (i > (columns * rows) - columns && i < (columns * rows) - 1) {
            board[i].AddNextTo(&board[i - columns - 1]);
            board[i].AddNextTo(&board[i - columns]);
            board[i].AddNextTo(&board[i - columns + 1]);
            board[i].AddNextTo(&board[i - 1]);
            board[i].AddNextTo(&board[i + 1]);
        }
        else if (i % columns == 0) {
            board[i].AddNextTo(&board[i + 1]);
            board[i].AddNextTo(&board[i + 1 - columns]);
            board[i].AddNextTo(&board[i + 1 + columns]);
            board[i].AddNextTo(&board[i + columns]);
            board[i].AddNextTo(&board[i - columns]);
        }
        else if ((i + 1) % columns == 0) {
            board[i].AddNextTo(&board[i - 1]);
            board[i].AddNextTo(&board[i - columns]);
            board[i].AddNextTo(&board[i + columns]);
            board[i].AddNextTo(&board[i - 1 - columns]);
            board[i].AddNextTo(&board[i - 1 + columns]);
        }

        // Surrounding of all other cells
        else {
            board[i].AddNextTo(&board[i-1]);
            board[i].AddNextTo(&board[i - 1 + columns]);
            board[i].AddNextTo(&board[i - 1 - columns]);
            board[i].AddNextTo(&board[i + 1]);
            board[i].AddNextTo(&board[i + 1 + columns]);
            board[i].AddNextTo(&board[i + 1 - columns]);
            board[i].AddNextTo(&board[i + columns]);
            board[i].AddNextTo(&board[i - columns]);
        }
    }
}

void Board::SetSurroundNumbers() {
    for (unsigned int i = 0; i < board.size(); i++) {

        
        if (!(board.at(i).getHiddenState() == Cell::HiddenState::MINE)) {
            int count = 0;

            
            for (unsigned int j = 0; j < board.at(i).GetSurroundCount(); j++) {
                Cell* current = board[i].GetSurround(j);
                if (current->getHiddenState() == Cell::HiddenState::MINE)
                    count += 1;
            }

            
            if (count == 1)
                board[i].setHiddenState(Cell::HiddenState::ONE);
            else if (count == 2)
                board[i].setHiddenState(Cell::HiddenState::TWO);
            else if (count == 3)
                board[i].setHiddenState(Cell::HiddenState::THREE);
            else if (count == 4)
                board[i].setHiddenState(Cell::HiddenState::FOUR);
            else if (count == 5)
                board[i].setHiddenState(Cell::HiddenState::FIVE);
            else if (count == 6)
                board[i].setHiddenState(Cell::HiddenState::SIX);
            else if (count == 7)
                board[i].setHiddenState(Cell::HiddenState::SEVEN);
            else if (count == 8)
                board[i].setHiddenState(Cell::HiddenState::EIGHT);
            else
                board[i].setHiddenState(Cell::HiddenState::EMPTY);
        }
    }
}

void Board::RevealCell(Cell* cell) {
    bool end = cell->RevealCell();
    if (end)
        SetGameOver();
}

void Board::Flag(Cell* cell) {
    cell->ToggleFlag(debug);
}

bool Board::GetVictory() {
    int count = 0;
    for (unsigned int i = 0; i < GetSize(); i++) {
        if (board[i].getState() == Cell::State::REVEAL)
            count += 1;
    }
    if (GetSize() - count - mines == 0) {
        for (unsigned int j = 0; j < board.size(); j++) {
            board[j].SetClickability(false);
            board[j].SetRightClickability(false);
            if (board[j].getHiddenState() == Cell::HiddenState::MINE) {
                board[j].SetSprite("flag");
            }
        }
        win = true;
        return true;
    }
    return false;
}

int Board::GetFlagCount() {
    flags = 0;
    for (unsigned int i = 0; i < GetSize(); i++) {
        if (board[i].getState() == Cell::State::FLAG)
            flags += 1;
    }
    return flags;
}

int Board::GetMineCount() {
    return mines;
}
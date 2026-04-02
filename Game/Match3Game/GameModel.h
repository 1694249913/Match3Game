#pragma once
#include"Cell.h"
#include"Board.h"

class GameModel
{
public :
	GameModel(int rows, int cols, int colorCount);
	//=================只读接口====================
	const Board& getBoard() const { return m_board; }
	Cell* getSelectedCell() const { return m_selectedCell; }
	int getScore() const { return m_score; }
	int getMoves() const { return m_moves; }
	const Cell* getCellConst(int row, int col) const { return m_board.getCellConst(row, col); } // 自动选 const 版本
	Cell* getCell(int row, int col) { return m_board.getCell(row, col); } // 自动选非 const 版本
	
	//=================修改接口====================
	void setSelectedCell(  Cell* cell) { m_selectedCell = cell; }
	void clearSelectedCell() { m_selectedCell = nullptr; }
	void swapCells(const Cell& cell_a, const Cell& cell_b) { m_board.swap(cell_a, cell_b); }
	void addScore(int delta) { m_score += delta; }
	void addMove() { m_moves++; }
	void setCellType(const Cell* cell, int type) { m_board.setCell(cell->getRow(),cell->getCol(), type); }
private:
	Cell *m_selectedCell;
	Board m_board;
	int m_score;
	int m_moves;
};
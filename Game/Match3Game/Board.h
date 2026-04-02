#pragma once
#include"Cell.h"
#include<vector>
#include<cassert>
class Board
{
public:
	Board(int rows,int cols,int colorCount);
	~Board()=default;
	void setCell(int row, int col, int type);
    Cell*getCell(int row, int col) ;
	const Cell* getCellConst(int row, int col)const;
	void randomFill();
	bool wouldCreateMatch(int row, int col);
	int getRows()const { return m_rows; }
	int getCols()const { return m_cols; }
	void swap(const Cell& cell_a, const Cell& cell_b);

private:
	int m_rows, m_cols, m_colorCount;
	std::vector<std::vector<Cell>>m_grid;
};
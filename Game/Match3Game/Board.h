#pragma once
class Board
{
public:
	Board(int rows,int cols,int colorCount);
	~Board();
	int getCell(int row, int col)const;
	void setCell(int row, int col, int type);
	void randomFill();
	bool wouldCreateMatch(int row, int col);
	int getRows()const { return m_rows; }
	int getCols()const { return m_cols; }

private:
	int m_rows, m_cols, m_colorCount;
	int** m_grid;
};
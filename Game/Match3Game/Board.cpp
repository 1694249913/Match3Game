// Board.cpp
#include "Board.h"
#include <cstdlib>
#include <ctime>

Board::Board(int rows, int cols, int colorCount)
    : m_rows(rows), m_cols(cols), m_colorCount(colorCount)
{
    // 动态分配二维数组
    m_grid = new int* [rows];
    for (int i = 0; i < rows; i++) 
    {
        m_grid[i] = new int[cols];
    }

    randomFill();
}

Board::~Board()
{
    for (int i = 0; i < m_rows; i++) 
    {
        delete[] m_grid[i];
    }
    delete[] m_grid;
}

int Board::getCell(int row, int col) const 
{
    if (row >= 0 && row < m_rows && col >= 0 && col < m_cols) 
    {
        return m_grid[row][col];
    }
    return 0;
}

void Board::setCell(int row, int col, int type) 
{
    if (row >= 0 && row < m_rows && col >= 0 && col < m_cols) 
    {
        m_grid[row][col] = type;
    }
}
void Board::randomFill() {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            do {
                m_grid[i][j] = rand() % m_colorCount + 1;
            } while (wouldCreateMatch(i, j));  // 如果会形成三连，重新随机
        }
    }
}

bool Board::wouldCreateMatch(int row, int col) {
    if (row < 2) return false;
    // 检查水平方向：左边两个是否和当前相同
    if (col >= 2 &&
        m_grid[row][col - 1] == m_grid[row][col] &&
        m_grid[row][col - 2] == m_grid[row][col]) {
        return true;
    }
    // 检查垂直方向：上边两个是否和当前相同
    if (row >= 2 &&
        m_grid[row - 1][col] == m_grid[row][col] &&
        m_grid[row - 2][col] == m_grid[row][col]) {
        return true;
    }
    return false;
}
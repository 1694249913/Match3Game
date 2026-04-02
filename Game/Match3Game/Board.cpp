// Board.cpp
#include "Board.h"
#include <cstdlib>
#include <ctime>

Board::Board(int rows, int cols, int colorCount)
    : m_rows(rows), m_cols(cols), m_colorCount(colorCount)
{
    // 动态分配二维数组
    m_grid.resize(rows, (std::vector<Cell>(cols)));
   
    randomFill();
}
// 常量版本：外部只读使用
const Cell*Board:: getCellConst(int row, int col)const
{
    assert(row >= 0 && row < m_rows && col >= 0 && col < m_cols);
    return &m_grid[row][col];
}

// 非常量版本：内部修改使用
Cell* Board::getCell(int row, int col)
{
    assert(row >= 0 && row < m_rows && col >= 0 && col < m_cols);
    return &m_grid[row][col];
}

void Board::setCell(int row, int col,int type)
{
    if (0 < type && type <=m_colorCount)
        m_grid[row][col].setType(type);
    else return;
}

void Board::randomFill() {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            m_grid[i][j].setRow(i);
            m_grid[i][j].setCol(j);
            do {
                m_grid[i][j].setType(rand() % m_colorCount + 1);
            } while (wouldCreateMatch(i, j));  // 如果会形成三连，重新随机
        }
    }
}
bool Board::wouldCreateMatch(int row, int col) {
    if (row < 2) return false;
    // 检查水平方向：左边两个是否和当前相同
    if (col >= 2 &&
        m_grid[row][col - 1].getType() == m_grid[row][col].getType() &&
        m_grid[row][col - 2].getType() == m_grid[row][col].getType()) {
        return true;
    }
    // 检查垂直方向：上边两个是否和当前相同
    if (row >= 2 &&
        m_grid[row - 1][col].getType() == m_grid[row][col].getType() &&
        m_grid[row - 2][col].getType() == m_grid[row][col].getType()) {
        return true;
    }
    return false;
}
void Board:: swap(const Cell& cell_a, const Cell& cell_b)
{

}
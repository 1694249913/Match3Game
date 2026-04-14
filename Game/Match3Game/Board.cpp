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
// Board.cpp
bool Board::hasMatch() const {
    // 水平方向检测
    for (int i = 0; i < m_rows; i++) {
        int count = 1;
        int lastType = getCellConst(i, 0)->getType();
        for (int j = 1; j < m_cols; j++) {
            int type = getCellConst(i, j)->getType();
            if (type != 0 && type == lastType) {
                count++;
                if (count >= 3) return true;
            }
            else {
                count = 1;
                lastType = type;
            }
        }
    }
    // 垂直方向检测
    for (int j = 0; j < m_cols; j++) {
        int count = 1;
        int lastType = getCellConst(0, j)->getType();
        for (int i = 1; i < m_rows; i++) {
            int type = getCellConst(i, j)->getType();
            if (type != 0 && type == lastType) {
                count++;
                if (count >= 3) return true;
            }
            else {
                count = 1;
                lastType = type;
            }
        }
    }
    return false;
}
std::vector<Cell*>Board::getMatchPositions()
{
    std::vector<Cell*> matches;
    std::vector<std::vector<bool>> marked(m_rows, std::vector<bool>(m_cols, false));

    // 水平方向
    for (int i = 0; i < m_rows; i++) {
        int len = 1;
        for (int j = 1; j <= m_cols; j++) {
            if (j < m_cols && getCellConst(i, j)->getType() != 0 &&
                getCellConst(i, j)->getType() == getCellConst(i, j - 1)->getType()) {
                len++;
            }
            else {
                if (len >= 3) {
                    for (int k = j - len; k < j; k++) {
                        if (!marked[i][k]) {
                            marked[i][k] = true;
                            matches.push_back(getCell(i, k)); // 非 const 版本
                        }
                    }
                }
                len = 1;
            }
        }
    }

    // 垂直方向
    for (int j = 0; j < m_cols; j++) {
        int len = 1;
        for (int i = 1; i <= m_rows; i++) {
            if (i < m_rows && getCellConst(i, j)->getType() != 0 &&
                getCellConst(i, j)->getType() == getCellConst(i - 1, j)->getType()) {
                len++;
            }
            else {
                if (len >= 3) {
                    for (int k = i - len; k < i; k++) {
                        if (!marked[k][j]) {
                            marked[k][j] = true;
                            matches.push_back(getCell(k, j));
                        }
                    }
                }
                len = 1;
            }
        }
    }
    return matches;
}
void Board::applyGravity() {
    for (int j = 0; j < m_cols; j++) {
        // 从下往上收集非空格子
        std::vector<int> columnTypes;
        for (int i = m_rows - 1; i >= 0; i--) {
            int type = getCellConst(i, j)->getType();
            if (type != 0) {
                columnTypes.push_back(type);
            }
        }
        // 从下往上填充
        for (int i = 0; i < m_rows; i++) {
            if (i < columnTypes.size()) {
                getCell(m_rows - 1 - i, j)->setType(columnTypes[i]);
            }
            else {
                getCell(m_rows - 1 - i, j)->setType(0);
            }
        }
    }
}

void Board::refill() {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            if (getCellConst(i, j)->getType() == 0) {
                int newType = rand() % m_colorCount + 1;
                getCell(i, j)->setType(newType);
            }
        }
    }
}

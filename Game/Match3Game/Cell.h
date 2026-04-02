#pragma once
#include <graphics.h>
// Cell.h
class Cell {
public:
    Cell(int row = -1, int col = -1, int type = 0);  // 默认构造函数
    ~Cell() = default;

    // 行列操作
    void setRow(int row);
    void setCol(int col);
    int getRow() const;
    int getCol() const;

    // 类型操作
    void setType(int type);
    int getType() const;

private:
    int row;
    int col;
    int type;
};
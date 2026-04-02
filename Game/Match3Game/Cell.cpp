// Cell.cpp
#include "Cell.h"

Cell::Cell(int row, int col, int type)
    : row(row), col(col), type(type) {}

void Cell::setRow(int row) { this->row = row; }
void Cell::setCol(int col) { this->col = col; }
int Cell::getRow() const { if (!this)return -1; return row; }
int Cell::getCol() const { if (!this)return -1; return col; }
void Cell::setType(int type) { this->type = type; }
int Cell::getType() const { return type; }
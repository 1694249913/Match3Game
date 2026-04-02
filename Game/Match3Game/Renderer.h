// Renderer.h
#pragma once
#include "Board.h"
#include <graphics.h>
#include"Types.h"
class Renderer {
public:
    Renderer(int cellSize, int offsetX, int offsetY, int rows, int cols);
    ~Renderer();
    POINT screenToGrid( int screenX, int screenY) const;
    void drawAll(const Board& board,  Cell*cell );
    void drawBoard(const Board& board,  Cell* cell);
    void drawScore(const Board& board);
    void drawButton(int x, int y, bool pressed);

private:
    int m_cellSize, m_offsetX, m_offsetY;
    int m_width, m_height;
    int m_rows, m_cols;
};
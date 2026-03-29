// Renderer.h
#pragma once
#include "Board.h"
#include <graphics.h>
#include"Types.h"
class Renderer {
public:
    Renderer(int cellSize, int offsetX, int offsetY, int rows, int cols);
    ~Renderer();
    void drawAll(const Board& board);
    void drawBoard(const Board& board);
    void drawScore(const Board& board);
    void drawButton(int x, int y, bool pressed);
private:
    int m_cellSize, m_offsetX, m_offsetY;
    int m_width, m_height;
};
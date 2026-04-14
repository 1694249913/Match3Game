// Renderer.cpp
#include "Renderer.h"
#include "ResourceManager.h"
#include <graphics.h>
#include <iostream>

Renderer::Renderer(int cellSize, int offsetX, int offsetY, int rows, int cols)
    : m_cellSize(cellSize), m_offsetX(offsetX), m_offsetY(offsetY),m_rows(rows), m_cols(cols)
{
    m_width = cols * cellSize + offsetX * 2;
    m_height = rows * cellSize + offsetY * 2+50+45;

    initgraph(m_width, m_height);
    setbkcolor(WHITE);
}
Renderer::~Renderer() { closegraph(); }
POINT Renderer::screenToGrid(int screenX, int screenY) const
{
    int gridX = screenX - m_offsetX;
    int gridY = screenY - m_offsetY;
    if (gridX < 0 || gridY < 0) return { -1, -1 };

    int col = gridX / m_cellSize;
    int row = gridY / m_cellSize;

    if (row >= 0 && row < m_rows && col >= 0 && col < m_cols)
        return { row, col };
    else  return {-1, -1};
    
}

void Renderer::drawAll(const Board& board,  Cell* cell)
{
    putimage(0, 0, &ResourceManager::getInstance().bgImage);
    drawBoard(board, cell);
    drawScore(board);
}

void Renderer::drawBoard( const Board& board,  Cell* cell)
{
    int gap = 6;                     // 缝隙宽度（像素）
    int drawSize = m_cellSize - gap; // 实际绘制尺寸
    int radius = 25;  // 圆角大小

    for (int i = 0; i < board.getRows(); i++) {
        for (int j = 0; j < board.getCols(); j++) {
           
            int x = m_offsetX + j * m_cellSize + gap / 2;
            int y = m_offsetY + i * m_cellSize + gap / 2;
            int type = board.getCellConst(i, j)->getType();

            IMAGE* img = ResourceManager::getInstance().getImage(type);
            if (img) {
                putimage_alpha(x, y, drawSize, drawSize,img);
            }
            else {
                // 如果没有图片，画灰色方块
                setfillcolor(RGB(100, 100, 100));
                solidrectangle(x, y, x + drawSize, y + drawSize);
            }
        }
    }
    // 第二遍：绘制选中格子的高亮（在所有格子之上，避免遮挡）
    if (cell) {
        int row = cell->getRow();
        int col = cell->getCol();
        int actualX = m_offsetX + col * m_cellSize + gap / 2;
        int actualY = m_offsetY + row * m_cellSize + gap / 2;
        int actualW = m_cellSize - gap;
        int actualH = m_cellSize - gap;

        // 外发光
        setlinecolor(RGB(255, 255, 0));
        setlinestyle(PS_SOLID, 3);
        roundrect(actualX - 2, actualY - 2, actualX + actualW + 2, actualY + actualH + 2, radius, radius);

        // 内边框
        setlinecolor(RGB(255, 200, 0));
        setlinestyle(PS_SOLID, 2);
        roundrect(actualX, actualY, actualX + actualW, actualY + actualH, radius, radius);

        setlinestyle(PS_SOLID, 1);
    }
}

void Renderer::drawScore(const Board& board)
{

}
void Renderer::drawButton(int x, int y,  bool pressed) 
{
    if (pressed)  putimage_alpha(x, y, &ResourceManager::getInstance().buttonImageDown);
    else  putimage_alpha(x, y, &ResourceManager::getInstance().buttonImage);
}
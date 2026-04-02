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
    for (int i = 0; i < board.getRows(); i++) {
        for (int j = 0; j < board.getCols(); j++) {
           
            int x = m_offsetX + j * m_cellSize;
            int y = m_offsetY + i * m_cellSize;
            int type = board.getCellConst(i, j)->getType();

            int radius = 25;  // 圆角大小
            setfillcolor(RGB(80, 120, 40));  // 深绿色 // 浅绿色色背景
            roundrect(x, y, x + m_cellSize, y + m_cellSize, radius, radius);
           
            
            IMAGE* img = ResourceManager::getInstance().getImage(type);
            if (img) {
                putimage_alpha(x, y, img);
                if (cell&&cell==board.getCellConst(i, j))
                {
                    int y = m_offsetX + cell->getRow() * m_cellSize;
                    int x = m_offsetY + cell->getCol() * m_cellSize;
                    setfillcolor(RGB(100, 100, 100));
                    solidrectangle(x, y, x + m_cellSize, y + m_cellSize);
                }
                   

            }
            else {
                // 如果没有图片，画灰色方块
                setfillcolor(RGB(100, 100, 100));
                solidrectangle(x, y, x + m_cellSize, y + m_cellSize);
            }

            // 画边框
           // setlinecolor(RGB(150, 150, 150));
            //rectangle(x, y, x + m_cellSize, y + m_cellSize);
        }
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
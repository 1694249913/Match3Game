// Game.cpp
#include "Game.h"
#include <conio.h>

Game::Game(int rows, int cols, int colorCount, int cellSize, int offsetX, int offsetY)
    : m_board(rows, cols, colorCount)
    , m_renderer(cellSize, offsetX, offsetY, rows, cols)
    , m_running(true)
{
    // 加载图片
    ResourceManager::getInstance().loadImages(cellSize);
}

Game::~Game() { }

void Game::render() {
    m_renderer.drawAll(m_board);
    m_renderer.drawButton(BTN_X, BTN_Y, m_buttonPressed);
    // ... 其他绘制
}
void Game::processInput() {
    if (MouseHit()) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            if (isPointInRect(msg.x, msg.y, BTN_X, BTN_Y,50,50)) {
                m_buttonPressed = true;
                m_buttonPressTime = GetTickCount();
                ResourceManager::getInstance().setActiveImages();
                return;
            }
            // ... 其他点击处理
            
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            m_running = false;
        }

    }
}
void Game::run()
{
    ExMessage msg;
    const int FPS = 60;
    BeginBatchDraw();
    while (m_running)
    {
        processInput();
        
        if (GetTickCount() - m_buttonPressTime > BUTTON_PRESS_DURATION) {
            m_buttonPressed = false;
        }
        cleardevice();
        render();
        FlushBatchDraw();
    }
    EndBatchDraw();
    return ;
}

// Game.h
#pragma once
#include "Board.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Types.h"

class Game {
public:
    Game(int rows, int cols, int colorCount, int cellSize, int offsetX, int offsetY);
    ~Game();
    void run();
    void processInput();
    void render();
private:
    Board m_board;
    Renderer m_renderer;
    bool m_running;

    bool m_buttonPressed;
    DWORD m_buttonPressTime;
    static const DWORD BUTTON_PRESS_DURATION = 100;  // 按下效果持续100ms
public :
    // Game.h 添加常量
    const int BTN_X = 20;
    const int BTN_Y = 560;  // 棋盘下方
};
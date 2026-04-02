// Game.cpp
#include "Game.h"
#include"Cell.h"
#include <conio.h>
Game::Game(int rows, int cols, int colorCount, int cellSize, int offsetX, int offsetY)
    : m_gameModel(rows, cols, colorCount)
    , m_renderer(cellSize, offsetX, offsetY, rows, cols)
    , m_running(true)
    , m_idle_state()        // 传入 this
    , m_selected_state()
    , current_state(&m_idle_state)
{
    // 加载图片
    ResourceManager::getInstance().loadImages(cellSize);
}
void Game::executeCommand(Command* cmd) {
    m_commandQueue.push(cmd);
}
void Game::processCommands() {
    while (!m_commandQueue.empty()) {
        Command* cmd = m_commandQueue.front();
        m_commandQueue.pop();

        // 执行命令
        cmd->execute(m_gameModel);

        // 存入历史（用于撤销）
        m_history.push(cmd);
    }
}
void Game::undo() {
    if (!m_history.empty()) {
        Command* cmd = m_history.top();
        m_history.pop();
        cmd->undo(m_gameModel);
        delete cmd;
    }
}

void Game::render() {
    m_renderer.drawAll(m_gameModel.getBoard(), m_gameModel.getSelectedCell());
    m_renderer.drawButton(BTN_X, BTN_Y, m_buttonPressed);  
}
void Game::processInput(const ExMessage&msg) {
   
        if (msg.lbutton) {
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
void Game::chageState(StateType state)
{
    current_state->on_exist();
    switch (state)
    {
    case StateType::Idle :
        current_state =& m_selected_state;
        break;
    case StateType::Select:
        current_state = &m_selected_state;
        break;
    case StateType::Matching:
        current_state = &m_selected_state;
        break;
    case StateType::Eliminating:
        current_state = &m_selected_state;
        break;
    case StateType::Swapping:
    default:
        break;
    }
    current_state->on_enter();
}
void Game::run()
{
   
    ExMessage msg;
    const int FPS = 60;
    BeginBatchDraw();
    while (m_running)
    {
        DWORD start_time = GetTickCount();
        while (peekmessage(&msg)) {
            if(msg.lbutton&&msg.y> BTN_Y)processInput(msg);
            else  current_state->on_input(*this,msg);
        }
        processCommands();
        static DWORD last_tick_time = GetTickCount();
        DWORD current_tick_time = GetTickCount();
        DWORD delta_tick = current_tick_time - last_tick_time;

        if (GetTickCount() - m_buttonPressTime > BUTTON_PRESS_DURATION) m_buttonPressed = false;

        current_state->on_update(*this,delta_tick);

        cleardevice();
        render();
        FlushBatchDraw();

        DWORD end_time = GetTickCount();
        DWORD delta_time = end_time - start_time;
        if (delta_time < 1000 / FPS)
            Sleep(1000 / FPS - delta_time);
    }
    EndBatchDraw();
    return ;
}
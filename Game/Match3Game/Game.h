
// Game.h
#pragma once
#include "Board.h"
#include "Renderer.h"
#include "State.h"
#include "IdleState.h"
#include "SelectedState.h"
#include "ResourceManager.h"
#include "Types.h"
#include "GameModel.h"
#include"Command.h"
#include<queue>
#include<stack>
class Game {
public:
    enum class StateType { Idle, Select, Matching, Eliminating, Swapping };
public:
    Game(int rows, int cols, int colorCount, int cellSize, int offsetX, int offsetY);
    ~Game()=default;
    void run();
   
    void processInput(const ExMessage& msg);
    void render();
    void chageState(StateType state);
    
    //==========命令系统=========
    void executeCommand(Command* cmd);//命令入队
    void processCommands();//执行命令
    void undo();//撤销

    //=========状态调用接口=========
    GameModel& getModel() { return m_gameModel; }
    POINT screenToGrid(int x, int y) const { return m_renderer.screenToGrid(x, y); }
    
    //========供渲染器调用的接口=========
    const GameModel& getModel()const { return m_gameModel; }
private:
   
    Renderer m_renderer;
    GameModel m_gameModel;

    State* current_state = nullptr;
    IdleState m_idle_state;
    SelectedState m_selected_state;
    bool m_running;
    bool m_buttonPressed;

    DWORD m_buttonPressTime;
    static const DWORD BUTTON_PRESS_DURATION = 100;  // 按下效果持续100ms
    // Game.h 添加常量
    static const int BTN_X = 20;
    static const int BTN_Y = 560;  // 棋盘下方
    std::queue<Command*>m_commandQueue;
    std::stack<Command*>m_history;
   
};
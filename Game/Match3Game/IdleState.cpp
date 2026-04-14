#include"IdleState.h"
#include<iostream>
#include"Game.h"
#include"SelectedCommand.h"
void IdleState::on_enter(){   std::cout << "idle已进入！" << std::endl;}
void IdleState::on_input(Game&m_game,const ExMessage& msg)
{
    // 只处理左键按下
    if (msg.lbutton) 
    {
        // 将屏幕坐标转换为格子坐标
        POINT clicked = m_game.screenToGrid(msg.x, msg.y);
        if (clicked.x != -1)
        {  
           Cell*cell= m_game.getModel().getCell(clicked.x, clicked.y);
           Command* cmd = new SelectedCommand(cell);
           m_game.executeCommand(cmd);
           std::cout << "选中命令入队!" << std::endl;
          
           m_game.chageState(Game::StateType::Select); // 需要 Game 提供 getSelectedState()
         
        }
    }
}
void IdleState::on_update(Game& m_game,int delta){  }
void IdleState::on_exist() { std::cout << "idle已退出！" << std::endl; }

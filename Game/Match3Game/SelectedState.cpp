#include"SelectedState.h"
#include<iostream>
#include"Game.h"
#include"SelectedCommand.h"
#include"SwapCommand.h"
void SelectedState::on_enter()
{
	std::cout << "selected已进入！" << std::endl;
}
void SelectedState::on_update(Game&m_game,int delta)
{
	
}
void SelectedState::on_input(Game&m_game,const ExMessage& msg)
{
    //std::cout << "选中格子信息为：" << m_game.getModel().getSelectedCell()->getCol()<< m_game.getModel().getSelectedCell()->getRow() << std::endl;

        if (!msg.lbutton) return;

        POINT clicked = m_game.screenToGrid(msg.x, msg.y);
        if (clicked.x == -1) return;
        
        Cell* selectedCell = m_game.getModel().getSelectedCell();
        Cell* clickedCell = m_game.getModel().getCell(clicked.x , clicked.y);
        int row1 = selectedCell->getRow();
        int col1 = selectedCell->getCol();
        int row2 = clicked.x;
        int col2 = clicked.y;

        if (!selectedCell) {
            // 没有选中？应该是 Idle 状态才对，防御
            m_game.chageState(Game::StateType::Idle);
            return;
        }
        if (row1 == row2 && col1 == col2) {
            // 同一个格子：取消选中
            m_game.executeCommand(new SelectedCommand(nullptr)); // 清除选中
            std::cout << "选中命令入队!--清空执行" << std::endl;
            m_game.chageState(Game::StateType::Idle);
        }
        else if (abs(row1 - row2) + abs(col1 - col2) == 1) {
            Command* cmd = new SwapCommand(selectedCell, clickedCell);
            m_game.executeCommand(cmd);
            std::cout << "交换命令入队!" << std::endl;

            // 清除选中（无论交换是否有效，选中都取消）
            m_game.getModel().clearSelectedCell();

            // 切换到交换状态（内部跳转MatchingState 去判断是否有匹配）
            m_game.chageState(Game::StateType::Swapping);
        }
        else {
            // 不相邻，更新选中为新格子
            m_game.getModel().setSelectedCell(clickedCell);
        }
}
void SelectedState::on_exist()
{
    std::cout << "selected退出！" << std::endl;
}
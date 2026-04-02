#include"SelectedState.h"
#include<iostream>
#include"Game.h"
void SelectedState::on_enter()
{
	std::cout << "selected已进入！" << std::endl;
	
}
void SelectedState::on_update(Game&m_game,int delta)
{
	std::cout << "选中格子信息为：" << m_game.getModel().getSelectedCell()->getCol()
		<< m_game.getModel().getSelectedCell()->getRow() << std::endl;
}
void SelectedState::on_input(Game&m_game,const ExMessage& msg)
{
	
}
void SelectedState::on_exist()
{

}
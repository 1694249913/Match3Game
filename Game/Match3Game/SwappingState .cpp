#include"SwappingState.h"
#include<iostream>
#include"Game.h"
#include"SelectedCommand.h"
void SwappingState::on_enter() { std::cout << "SwappingState已进入！" << std::endl; }
void SwappingState::on_input(Game& m_game, const ExMessage& msg)
{ }
void SwappingState::on_update(Game& m_game, int delta) 
{
	m_game.processCommands();  // 执行 SwapCommand
	m_game.chageState(Game::StateType::Matching);
}
void SwappingState::on_exist() { std::cout << "SwappingState已退出！" << std::endl; }

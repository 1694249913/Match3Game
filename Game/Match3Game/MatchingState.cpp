#include "MatchingState.h"
#include "Game.h"
#include<iostream>
void MatchingState::on_enter() { std::cout << "match已进入！" << std::endl; }
void MatchingState::on_update(Game& m_game, int delta)
{
   
    if (m_game.getModel().getBoard().hasMatch()) {
        // 有匹配，进入消除状态（稍后实现）
        m_game.chageState(Game::StateType::Eliminating);
    }
    else {
        // 无匹配，回到空闲
        m_game.chageState(Game::StateType::Idle);
    }
}
void MatchingState::on_input(Game& m_game, const ExMessage& msg)
{}
void MatchingState::on_exist() { std::cout << "MatchingState已退出！" << std::endl; }
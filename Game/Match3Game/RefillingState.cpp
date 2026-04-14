#include "RefillingState.h"
#include "Game.h"
#include<iostream>


void RefillingState::on_enter() { std::cout << "RefillingState已进入！" << std::endl; }
void RefillingState::on_input(Game& m_game, const ExMessage& msg)
{  }
void RefillingState::on_update(Game& m_game, int delta)
{
    m_game.getModel().getBoard2().refill();
    // 再次进入匹配状态，检测新消除
    m_game.chageState(Game::StateType::Matching);
}
void RefillingState::on_exist() { std::cout << "RefillingState已退出！" << std::endl; }
#include "FallingState.h"
#include "Game.h"
#include<iostream>
void FallingState::on_enter() { std::cout << "FallingState已进入！" << std::endl; }
void FallingState::on_input(Game& m_game, const ExMessage& msg)
{  }
void FallingState::on_update(Game& m_game, int delta){
    m_game.getModel().getBoard2().applyGravity();
    m_game.chageState(Game::StateType::Refilling);
}
void FallingState::on_exist() { std::cout << "FallingState已退出！" << std::endl; }
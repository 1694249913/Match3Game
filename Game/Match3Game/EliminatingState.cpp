#include"EliminatingState.h"
#include<iostream>
#include"Game.h"
#include"SelectedCommand.h"
void EliminatingState::on_enter() { std::cout << "EliminatingState已进入！" << std::endl; }
void EliminatingState::on_input(Game& m_game, const ExMessage& msg)
{  }
void EliminatingState::on_update(Game& m_game, int delta)
{ 
    auto& model = m_game.getModel();
    auto matches = model.getBoard2().getMatchPositions();

    if (matches.empty()) {
        m_game.chageState(Game::StateType::Idle);
        return;
    }

    // 消除匹配的格子（设为0）
    for (Cell* cell : matches) {
        cell->setType(0);
    }

    // 加分
    //model.addScore(matches.size() * 10);

    // 进入掉落状态
    m_game.chageState(Game::StateType::Falling);
}
void EliminatingState::on_exist() { std::cout << "EliminatingState已退出！" << std::endl; }
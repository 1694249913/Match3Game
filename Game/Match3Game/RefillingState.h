#pragma once
#include"State.h"
class RefillingState :public State
{
public:

	void on_enter()override;
	void on_update(Game& m_game, int delta)override;
	void on_input(Game& m_game, const ExMessage& msg)override;
	void on_exist()override;
};
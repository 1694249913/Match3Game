#pragma once
#include <graphics.h>
class Game;
class State
{
public:
	virtual ~State() = default;
	virtual void on_enter()=0;
	virtual void on_update(Game &m_game,int delta)=0;
	virtual void on_input(Game& m_game, const ExMessage&msg)=0;
	virtual void on_exist()=0;

};
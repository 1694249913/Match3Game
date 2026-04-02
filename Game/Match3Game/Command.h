#pragma once
#include"GameModel.h"
class Command
{
public :
	virtual ~Command() = default;
	virtual void execute(GameModel& model) = 0;//执行操作
	virtual void undo(GameModel& model) = 0;//撤销操作
};

#pragma once
#include"Command.h"
#include"Cell.h"
class SelectedCommand :public Command
{
public :
	SelectedCommand( Cell *cell):m_cell(cell),m_oldcell(nullptr){}
	void execute(GameModel& model)override;
	void undo(GameModel& model)override;
private:
	Cell *m_cell;
	Cell *m_oldcell;
};
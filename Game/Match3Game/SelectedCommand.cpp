#include"SelectedCommand.h"
void SelectedCommand::execute(GameModel& model)
{
	m_oldcell = model.getSelectedCell();
	model.setSelectedCell(m_cell);
}
void SelectedCommand::undo(GameModel& model)
{
	model.setSelectedCell(m_oldcell);
}
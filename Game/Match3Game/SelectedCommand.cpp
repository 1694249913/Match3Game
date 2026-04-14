#include"SelectedCommand.h"
#include<iostream>
void SelectedCommand::execute(GameModel& model)
{
	m_oldcell = model.getSelectedCell();
	model.setSelectedCell(m_cell);
	std::cout << "选中命令并执行!" << std::endl;
	std::cout << "选中信息为：" <<m_cell->getRow()<<m_cell->getCol()<< std::endl;
	std::cout << "原始信息为：" << m_oldcell->getRow() << m_oldcell->getCol() << std::endl;
}
void SelectedCommand::undo(GameModel& model)
{
	model.setSelectedCell(m_oldcell);
	
}
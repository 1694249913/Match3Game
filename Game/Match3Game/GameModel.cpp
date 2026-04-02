#include"GameModel.h"
GameModel::GameModel(int rows, int cols, int colorCount)
	:m_board(rows,cols,colorCount)
	, m_selectedCell(nullptr)
	,m_score(0)
	,m_moves(0)
{}
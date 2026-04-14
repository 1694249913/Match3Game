#pragma once
#include"Command.h"
#include"Cell.h"
class SwapCommand :public Command
{
public:
    SwapCommand(Cell* a, Cell* b);
    void execute(GameModel& model) override;
    void undo(GameModel& model) override;
private:
    Cell* m_a;
    Cell* m_b;
    bool m_valid;   // 交换是否有效（产生了三消）
};
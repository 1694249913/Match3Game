#include "SwapCommand.h"
#include "GameModel.h"
#include <iostream>
SwapCommand::SwapCommand(Cell* a, Cell* b) : m_a(a), m_b(b), m_valid(false) {}

void SwapCommand::execute(GameModel& model) {
    // 交换两个格子的类型
    int typeA = m_a->getType();
    int typeB = m_b->getType();
    m_a->setType(typeB);
    m_b->setType(typeA);

    // 检查是否有三消
    if (model.getBoard().hasMatch()) {
        m_valid = true;
    }
    else {
        // 无效交换，换回来
        m_a->setType(typeA);
        m_b->setType(typeB);
        m_valid = false;
    }
    std::cout << "交换命令并执行!" << std::endl;
}

void SwapCommand::undo(GameModel& model) {
    if (m_valid) {
        // 再次交换恢复
        int typeA = m_a->getType();
        int typeB = m_b->getType();
        m_a->setType(typeB);
        m_b->setType(typeA);
    }
}
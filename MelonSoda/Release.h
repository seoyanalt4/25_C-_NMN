#pragma once
#include "Skill.h"

class Release : public Skill {
public:
    std::string name() const override { return "������ (���� 2, MP 4)"; }
    std::string description() const override {
        return "(���� HP �� 0.1) �� ���� ���� ���ø�ŭ ����";
    }
    int execute(Player& player, Monster& monster) override;
};
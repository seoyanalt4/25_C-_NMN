#pragma once
#include "Skill.h"

class Reflect : public Skill {
public:
    std::string name() const override { return "ƨ�ܳ��� (MP 4)"; }
    std::string description() const override {
        return "1�� ���� �޴� ������ 30% ���� + ���� +1";
    }
    int execute(Player& player, Monster& monster) override;
};
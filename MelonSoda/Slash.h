#pragma once
#include "Skill.h"

class Slash : public Skill {
public:
    std::string name() const override { return "���� (MP 3)"; }
    std::string description() const override {
        return "�ֱ� ������ 1.3�� ���� + ���� +1";
    }
    int execute(Player& player, Monster& monster) override;
};
#pragma once
#include "Skill.h"

class SwordOrder : public Skill {
public:
    std::string name() const override { return "�ҵ� ���� (���� 3, MP 4)"; }
    std::string description() const override {
        return "�ֱ� ������ 1.4�� ���� + ������ ���ݸ�ŭ HP ȸ��";
    }
    int execute(Player& player, Monster& monster) override;
};
#pragma once
#include <string>

class Player;
class Monster;

class Skill {
public:
    virtual ~Skill() = default;
    // ��ų ����
    virtual int execute(Player& player, Monster& monster) = 0;
    // �޴� ��¿� �̸�/����
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
};

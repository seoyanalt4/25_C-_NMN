#pragma once
#include "Actor.h"
#include <map>
#include <string>

class Player;

class Monster : public Actor {

public:
	Monster(std::string monster_name, int monster_HP, int monster_MP, int monster_ATK, int monster_DEF, int event_index = (rand() % 4 + 1));
	void showMStat();

	int Event_index;

	int hitDamage;

	//�����Լ� ���� ������ �뵵
	virtual int Get_Stack();
};

class Boss : public Monster {
public:
	using Monster::Monster;
	// �̷� ����: �� �ϸ��� +1
	int future = 0;

	// �÷��̾�� ���� �ֱ� ������
	int lastDamage = 20;

	// �� ���� ���� ������ ȣ�� HP +3, �̷� +1
	int regeneratePerTurn();
	// �ھ��� �̷� ��ų
	int overturnFuture();
	// ����� ���� ��ų
	int heavensDoor(Player& player);
	// �̰��� �� ��ų
	int otherworldlyBlade(Player& player);

	//�����Լ��� �̷� ���� ��������
	int Get_Stack();
};

extern Monster slime;
extern Monster king_slime;
extern Monster watterrat;
extern Monster chandelier;
extern Boss witch;

extern Monster zero;

inline std::map<int, Monster*> createMonsterMap() {
	std::map<int, Monster*> m;
	m[1] = &slime;
	m[2] = &king_slime;
	m[3] = &watterrat;
	m[4] = &chandelier;
	m[5] = &witch;
	return m;
}

extern std::map<int, Monster*> monsterMap;
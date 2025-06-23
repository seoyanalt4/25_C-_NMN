#pragma once
#include "Actor.h"
#include "Fruit.h"
#include "SkillFactory.h"
#include <vector>
#include <map>
#include <memory>
#include "Monster.h"

//�÷��̾�� �⺻���� ���
//�߰��� ��: �κ��丮, ���丮 ��ȣ(���丮 ������� ��¿�), �����ڿ� �̸� �Ű������� ����(�����ϴ� ����� �Է���), �������� �Լ���
class Player : public Actor {

public:
	std::vector<FRUIT> fruit_inventory;
	std::vector<DRINK> drink_inventory;
	int story_index;

	//�÷��̾� �⺻���� �� ����
	int concentration;
	//�ֱ� ���� �������� ����
	int lastDamage;
	//1�� ���� ������ ���� ���� ����
	bool isReflecting;
	//���� ������ ����
	int hitDamage;

	Player();

	void Setname(std::string input);

	//�÷��̾� ���� �����ִ� �Լ�
	/*void showPStat();*/
	//�÷��̾� �κ��丮 �����ִ� �Լ�
	void showInventory();
	//�÷��̾� �κ��丮�� ���� �߰��ϴ� �Լ�
	void addInventory(FRUIT fruit);
	//�÷��̾� �κ��丮���� ���� �����ϴ� �Լ�
	void useInventory(FRUIT fruit);
	//BLEND!
	void blendFruit(FRUIT fruit1, FRUIT fruit2);
	//�÷��̾� �κ��丮�� ����� �߰��ϴ� �Լ�
	void addDrink(DRINK drink);
	//�÷��̾� ���� �Լ�
	void addConcentration();
	// ��ų ��� �Լ�
	int useSkill(Monster& monster);
	// ��ų ��
	static std::map<int, std::unique_ptr<Skill>> skills;
};
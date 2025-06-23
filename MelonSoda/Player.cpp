#include "Player.h"
#include "SkillFactory.h"
#include "Monster.h"
#include "UIManager.h"

#include <iostream>
#include <algorithm>
#include <string>

// ��ų �� �ʱ�ȭ
std::map<int, std::unique_ptr<Skill>> Player::skills = createSkillMap();

Player::Player()
{
	name = "defalut name";
	HP = 50;
	MP = 5;
	ATK = 10;
	DEF = 5;

	//���� �ʱ�ȭ
	concentration = 0;
	//�ֱ� ���ݷ� ������ �ʱ�ȭ
	lastDamage = 0;
	//1�� ���� ������ ���� ���� ���� �ʱ�ȭ
	isReflecting = false;

	//���Ͽ� ���� ������ �ӽ�����
	hitDamage = 0;
}

void Player::Setname(std::string input)
{
	this -> name = input;
}

//void Player::showPStat() {
//	std::cout << "Name : " << name << std::endl;
//	std::cout << "HP : " << HP << std::endl;
//	std::cout << "MP : " << MP << std::endl;
//	std::cout << "ATK : " << ATK << std::endl;
//	std::cout << "DEF : " << DEF << std::endl;
//	std::cout << "concentration : " << concentration << std::endl;
//}

void Player::showInventory() {
	int num = 1;
	//�����ϰ� ����� �� �� �ϳ��̻� �����ÿ��� ǥ�ÿ�
	if (!fruit_inventory.empty()) {
		G_UI->PrintLog("---���� �ָӴ�---");
		for (const auto& item : fruit_inventory) {
			G_UI->PrintLog(num++ , " ", item.name);
		}
	}

	if (!drink_inventory.empty()) {
		G_UI->PrintLog("---���� �����---");
		for (const auto& item : drink_inventory) {
			G_UI->PrintLog(item.name);
		}
	}
}

void Player::addInventory(FRUIT fruit) {
	fruit_inventory.push_back(fruit);
	G_UI->PrintLog(fruit.name, "��(��) ȹ���ߴ�!");

	HP += fruit.HP;
	MP += fruit.MP;
	ATK += fruit.ATK;
	DEF += fruit.DEF;

	G_UI->PrintLog(fruit.name , "��(��) �ָӴϿ� �־���. ");
	if (fruit.HP != 0) G_UI->PrintLog("ü���� ", fruit.HP, " ��ȭ�ߴ�.");
	if (fruit.MP != 0) G_UI->PrintLog("������ ", fruit.MP, " ��ȭ�ߴ�.");
	if (fruit.ATK != 0) G_UI->PrintLog("���ݷ��� ", fruit.ATK, " ��ȭ�ߴ�.");
	if (fruit.DEF != 0) G_UI->PrintLog("������ ", fruit.DEF, " ��ȭ�ߴ�.");
}

void Player::useInventory(FRUIT fruit) {
	auto it = std::find(fruit_inventory.begin(), fruit_inventory.end(), fruit);
	if (it != fruit_inventory.end()) {
		G_UI->PrintLog(it->name , "�� ȿ���� �������.");
		HP -= it->HP;
		MP -= it->MP;
		ATK -= it->ATK;
		DEF -= it->DEF;

		//if (fruit.HP != 0) std::cout << "ü���� " << it->HP << " ";
		//if (fruit.MP != 0) std::cout << "������ " << it->MP << " ";
		//if (fruit.ATK != 0) std::cout << "���ݷ��� " << it->ATK << " ";
		//if (fruit.DEF != 0) std::cout << "������ " << it->DEF << " ";
		//std::cout << "�����ߴ�." << std::endl;

		fruit_inventory.erase(it);
	}
	else {
		G_UI->PrintLog( "�ش� �������� �����ϴ�.");
	}
}

//������ �ߺ��̵巡��~
void Player::blendFruit(FRUIT fruit1, FRUIT fruit2) {
	useInventory(fruit1);
	useInventory(fruit2);
	DRINK temp;
	temp = fruit1 + fruit2;
	addDrink(temp);
}

void Player::addDrink(DRINK drink)
{
	drink_inventory.push_back(drink);
	G_UI->PrintLog(drink.name , "��(��) �������!");

	HP += drink.HP;
	MP += drink.MP;
	ATK += drink.ATK;
	DEF += drink.DEF;

	G_UI->PrintLog( drink.name, "��(��) ���̴�. ");
	if (drink.HP != 0) G_UI->PrintLog("ü���� ", drink.HP, " �����ߴ�.");
	if (drink.MP != 0) G_UI->PrintLog("������ ", drink.MP, " �����ߴ�.");
	if (drink.ATK != 0) G_UI->PrintLog("���ݷ��� ", drink.ATK , " �����ߴ�.");
	if (drink.DEF != 0) G_UI->PrintLog("������ " , drink.DEF , " �����ߴ�.");

}

//���� ���� �Լ�
void Player::addConcentration() {
	concentration++;
	ATK += 2;
	DEF += 2;
	MP += 2;
	G_UI->PrintLog("���⸦ ��Ҵ�! ���� ����: ", concentration);
	G_UI->PrintLog("���ݷ�, ����, ������ ���� 2�� �����ߴ�!");
}

int Player::useSkill(Monster& monster) {
	G_UI->PrintLog("");
	G_UI->PrintLog("[��ų ���]");
	for (const auto& entry : skills) {
		int idx = entry.first;
		auto& skill = entry.second;
		/*G_UI->PrintLog(skill->name(), " - ", idx," , ", skill->name(), " - ", skill->description());*/
		G_UI->PrintLog(idx," - ",skill->name(), ",   - ", skill->description());

	}
	G_UI->PrintLog("��ų ��ȣ�� �Է��ϼ���: ");
	int choice;
	std::cin >> choice;

	auto it = skills.find(choice);
	if (it != skills.end()) {
		G_UI->showLog();
		return it->second->execute(*this, monster);
	}
	else {
		G_UI->PrintLog("�߸��� �����Դϴ�.");
	}
}
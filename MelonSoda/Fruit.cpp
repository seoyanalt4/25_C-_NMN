#include "Fruit.h"
#include "UIManager.h"

#include <iostream>
#include <map>

FRUIT::FRUIT(std::string fruit_name, int fruit_HP, int fruit_MP, int fruit_ATK, int fruit_DEF, int fruit_index) {
	name = fruit_name;
	HP = fruit_HP;
	MP = fruit_MP;
	ATK = fruit_ATK;
	DEF = fruit_DEF;
	Index = fruit_index;
}

bool FRUIT::operator==(const FRUIT& other) const {
	return name == other.name && Index == other.Index;
}

//����("�̸�", ü��, ����, ���ݷ�, ����, ������ȣ) ����� ��ȣ�� 1 2 4 8 16 32 64 128...�̷������� �ο��� ��
const FRUIT orange("������", 1, 0, 2, 0, 1);
const FRUIT apple("���",0, 2, 0, 2, 2);
const FRUIT grapefruit("�ڸ�", 0, 0, 3, -1, 4);
const FRUIT grape("����", 3, 0, -2, 0, 8);
const FRUIT avocado("�ƺ�ī��", 0, -2, 0, 2, 16);
const FRUIT watermelon("����", -3, 0, 2, -1, 32);

//�����("�̸�", ü��, ����, ���ݷ�, ����, ������ȣ) ����� ��ȣ�� ���� ������ȣ 2�������� �ο��� ��
const DRINK puresour("ǻ����", 0, 0, 4, 4, 1+2);
const DRINK twoblood("�� ��ε�", 5, 0, 6, 0, 1+4);
const DRINK darklip("��ũ ��", 3, 0, 0, 4, 1+8);
const DRINK unlock("���", 0, 0, 0, 7, 1+16);
const DRINK deepjune("�� ��", 0, 5, 0, 4, 2+4);
const DRINK heaven("���", 0, 2, 3, 3, 2+8);
const DRINK mellowyellow("��ο� ���ο�", 0, 0, 7, 0, 2+32);
const DRINK darkseed("��ũ�õ�", 4, 0, 6, 0, 4+8);
const DRINK oceanmood("���ǹ���", 3, 0, 0, 5, 4+16);
const DRINK sourshower("�������", 5, 0, 0, 3, 8+16);
const DRINK squished("�����õ�", 3, 3, 5, 0, 8+32);
const DRINK clearred("Ŭ���� ����", 6, 3, 5, 0, 16+32);
const DRINK unluckymelon("��Ű���", 5, 5, 5, 5, 32+32);

std::map<int, DRINK> drinkMap = {
    {1 + 2, puresour},
    {1 + 4, twoblood},
    {1 + 8, darklip},
    {1 + 16, unlock},
    {2 + 4, deepjune},
    {2 + 8, heaven},
    {2 + 32, mellowyellow},
    {4 + 8, darkseed},
    {4 + 16, oceanmood},
    {8 + 16, sourshower},
    {8 + 32, squished},
    {16 + 32, clearred},
    {32 + 32, unluckymelon}
};

DRINK operator+(const FRUIT& fruit1, const FRUIT& fruit2)
{
    int blendIndex = fruit1.Index + fruit2.Index;
    if (drinkMap.count(blendIndex)) {
        return drinkMap[blendIndex];
    }
    else {
        G_UI->PrintLog( "��...�� ���� ���չ��� ���� �ʾ�����?");
        return DRINK("�׳����� �����", 0, 0, 2, 2);
    }
}

#include "Monster.h"
#include "Player.h"
#include "UIManager.h"

#include <iostream>

Monster::Monster(std::string monster_name, int monster_HP, int monster_MP, int monster_ATK, int monster_DEF, int event_index) {
	name = monster_name;
	HP = monster_HP;
	MP = monster_MP;
	ATK = monster_ATK;
	DEF = monster_DEF;
	Event_index = event_index;

    //���Ͽ� ���� ������ �ӽ�����
    hitDamage = 0;

}

void Monster::showMStat() {
    G_UI->PrintLog( "Name : ", name);
    G_UI->PrintLog("HP : ", HP);
}

//��� ���� �ȵ� �������̵� ���� ����Ǹ� ��������
int Monster::Get_Stack()
{
    G_UI->clearALL();
    G_UI->PrintLog("������ �����Լ� ȣ��� �̰� �߸� ����");
    std::abort();
    return 0;
}

// Boss::regeneratePerTurn ����
int Boss::regeneratePerTurn() {
    // HP ȸ��
    HP += 3;
    // �̷� ���� ����
	future += 1;
    G_UI->PrintLog( name , "��(��) HP 3 ȸ��, �̷� ���� +1! " , "(HP: " , HP , ", �̷�: " , future , ")");
    return 0;
}

int Boss::overturnFuture() {
    if (future < 5) {
        //G_UI->PrintLog( name, " : �̷� ������ �����մϴ�. (�ʿ�:5, ����:" , future , ")");
        return 1;
    }
    future -= 5;

    G_UI->PrintLog(name, "�� Ư�� '�ھ��� �̷�' �ߵ�!");

    //(ATK / 3)��ŭ HP ȸ��
    HP += ATK / 3;
    G_UI->PrintLog( name , "��(��) ATK(" , ATK , ") / 3��ŭ HP ȸ�� �� HP: " , HP);

    //(�ֱ� ������ / 3) ��ŭ ȸ���� ���� ���ʽ� ����
    int bonusHeal = (lastDamage / 3);
    HP += bonusHeal;
    G_UI->PrintLog( "�ֱ� ������(" , lastDamage , ") / 3 = " , bonusHeal , " �߰� ȸ�� �� HP: " , HP);

    //ȸ�� �� HP ������ MP, �̷� ���� ����
    if (HP < 22) {
        MP += 3;
        G_UI->PrintLog("MP +3 ȹ��! (MP: " , MP , ")");
    }
    else if (HP < 25) {
        MP += 3;
        future += 1;
        G_UI->PrintLog("MP +3, �̷� +1 ȹ��! (MP: " , MP , ", �̷�: " , future , ")");
    }
    else {
        MP += 5;
        future += 2;
        G_UI->PrintLog( "MP +5, �̷� +2 ȹ��! (MP: " , MP , ", �̷�: " , future , ")");
    }
    return 0;
}

int Boss::heavensDoor(Player& player) {
    // MP 8 �Ҹ�
    if (MP < 8) {
        //G_UI->PrintLog(name , " : MP�� �����մϴ�. (�ʿ�:8, ����:" , MP , ")");
        return 1;
    }
    MP -= 8;

    // (�ֱ� ���� * 1.6) / 2 ��ŭ �÷��̾�� ������
    if (lastDamage < 1) {
        lastDamage = player.ATK;
    }

    int dmgValue = static_cast<int>((lastDamage * 1.6) / 2);
    player.HP -= dmgValue;
    player.hitDamage += dmgValue;
    G_UI->PrintLog( name , "��(��) '����� ����'�� �����ߴ�!");
    G_UI->PrintLog(player.name , "���� " , dmgValue , "��ŭ�� ���ظ� ������.");

    // �̷� ���� +1
    future += 1;
    G_UI->PrintLog( "�̷� ���� +1 (����: " , future , ")");

    // ��� ���� ���ظ� lastDamage�� ����
    lastDamage = dmgValue;
    return 0;
}

int Boss::otherworldlyBlade(Player& player) {
    // MP 5 �Ҹ�
    if (MP < 5) {
        //G_UI->PrintLog( name , " : MP�� �����մϴ�. (�ʿ�:5, ����:" , MP , ")");
        return 1;
    }
    // ���� HP�� 10% �Ҹ�
    int hpCost = static_cast<int>(HP * 0.1);
    HP -= hpCost;
    MP -= 5;

    G_UI->PrintLog( name , "��(��) ���̰��� �ˡ��� �����ϸ� HP ", hpCost , "�� ����ߴ�! (���� HP: " , HP , ")");

    // (�ֱٵ����� ��1.4) / 3 ��ŭ �÷��̾�� ����
    int dmgValue = static_cast<int>((lastDamage * 1.4) / 3);
    player.HP -= dmgValue;
    player.hitDamage += dmgValue;
    G_UI->PrintLog( player.name , "���� " , dmgValue , "��ŭ�� ���ظ� ������!");

    // ATK+2, DEF+1
    ATK += 2;
    DEF += 1;
    G_UI->PrintLog(name , "�� ���ݷ� ATK +2, ���� DEF +1 ���� ����! " , "(ATK: " , ATK , ", DEF: " , DEF , ")");

    // �ֱ� ������ ��� ����
    lastDamage = dmgValue;
    return 0;
}

//�̷����ù�ȯ UI���� ���
int Boss::Get_Stack()
{
    return future;
}
Monster slime("������", 24, 0, 5, 7);
Monster king_slime("ŷ������", 37, 0, 8, 11);
Monster watterrat("���ͷ�", 49, 5, 11, 15);
Monster chandelier("���鸮��", 61, 6, 13, 18);
Boss witch("����", 200, 7, 14, 20, 6);

std::map<int, Monster*> monsterMap = createMonsterMap();

//������ ����
Monster zero("����", 0, 0, 0, 0);

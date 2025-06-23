#include "Release.h"
#include "Player.h"
#include "Monster.h"
#include "UIManager.h"

#include <iostream>

int Release::execute(Player& player, Monster& monster) {
    if (player.concentration < 2) {
        G_UI->PrintLog( "���Ⱑ �����մϴ�. (�ʿ�:2, ����:" , player.concentration, ")");
        return 1;
    }
    if (player.MP < 4) {
        G_UI->PrintLog( "������ �����մϴ�. (�ʿ�:4, ����:" , player.MP, ")");
        return 1;
    }
    player.MP -= 4;
    // ((�÷��̾��� ���� hp) x 0.1) x (���� ����)
    int damage = static_cast<int>((player.HP * 0.1) * player.concentration);
    monster.HP -= damage;
    monster.hitDamage += damage;
    player.concentration -= 2;

    G_UI->PrintLog("[������ ��ų ���]");
    G_UI->PrintLog("- ���� HP�� 10% �� ���� ������ ���ط� ��ȯ!");
    G_UI->PrintLog("- " , monster.name , "���� " , damage , " �������� ������.");
    G_UI->PrintLog( "- ���� ���� 2�� �Ҹ�Ǿ����ϴ�. (����: " , player.concentration, ")");
    return 0;
}
#include "SwordOrder.h"
#include "Player.h"
#include "Monster.h"
#include "UIManager.h"

#include <iostream>

int SwordOrder::execute(Player& player, Monster& monster) {
    if (player.concentration < 3) {
        G_UI->PrintLog("���Ⱑ �����մϴ�. (�ʿ�:3, ����: ", player.concentration, ")");
        return 1;
    }
    if (player.MP < 4) {
        G_UI->PrintLog( "������ �����մϴ�. (�ʿ�:4, ����: ", player.MP, ")");
        return 1;
    }
    player.MP -= 4;
    player.concentration -= 3;

    int damage = static_cast<int>(player.lastDamage * 1.4);
    monster.HP -= damage;
    monster.hitDamage += damage;
    int heal = damage / 2;
    player.HP += heal;

    G_UI->PrintLog("");
    G_UI->PrintLog( "[�ҵ� ���� ��ų ���]" );
    G_UI->PrintLog(monster.name, "���� ", damage , " �������� ������.");
    G_UI->PrintLog("������ ����(" , heal , ") ��ŭ HP�� ȸ���ߴ�.");
    return 0;
}
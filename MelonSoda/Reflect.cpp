#include "Reflect.h"
#include "Player.h"
#include "Monster.h"
#include "UIManager.h"

#include <iostream>

int Reflect::execute(Player& player, Monster& monster) {
    if (player.MP < 4) {
        G_UI->PrintLog("������ �����մϴ�. (�ʿ�:4, ����:", player.MP, ")");
        return 1;
    }
    player.MP -= 4;
    player.concentration++;
    player.ATK += 2;
    player.DEF += 2;
    player.MP += 2;

    player.isReflecting = true;
    G_UI->PrintLog("");
    G_UI->PrintLog( "[ƨ�ܳ��� ��ų ���]");
    G_UI->PrintLog("- ������ ���� ���� ���ذ� 30% ���ҵ˴ϴ�.");
    G_UI->PrintLog("- ���� ���� +1 (����: " , player.concentration , "), ATK/DEF/MP +2");

    return 0;
}
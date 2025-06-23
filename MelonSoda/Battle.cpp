#include "Battle.h"
#include "Monster.h"
#include "Player.h"
#include "UIManager.h"

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <string>

//��Ʋ �Լ��� �ñ��ϸ� �о�� �����ϼſ�
void Battle(Player& player, Monster& monster)
{
	// ���� �б�
	bool didselect = FALSE;
	bool didevent = FALSE;
	
	if (auto bossPtr = dynamic_cast<Boss*>(&monster)) {
		if (!didevent) {
			G_UI->PrintLog("�̺�Ʈ BOSS <���������� '��'�̵� �̾߱�>");
			G_UI->PrintLog("����(???) : �׷��� ������ �ٴϴ°� ��̾�?");
			G_UI->PrintLog("            �� �ٺ���? ��... �װ� �� ����ε� ���ٰ� �ֿ��°ž�?");
			G_UI->PrintLog("            �� �̻� ���� ������ �����ϴ°� �����ž�. �� ȣ��ȣ������ �ʴٰ�");
			Sleep(2000);
			G_UI->PrintLog("��� : ���۽������� �������� ȭ�� �ٷ� �غ� �ؾ��� �� ����.");
			G_UI->PrintLog(player.name, " (��)�� ������ ����� Į�� �����");
			G_UI->PrintLog("������ ��������....!");
			Sleep(2000);
			didevent = TRUE;
		}
	}

	G_UI->PrintLog(monster.name, " ��(��) ��Ÿ����!");
	while ((player.HP > 0) && (monster.HP > 0)) {
		G_UI->PrintLog(player.name, "�� ����");
		int playerSelect = 0;
		int monsterSelect = 0;		//���� ai ������
		while (1) {
			G_UI->PrintLog("������ �ұ�?");
			G_UI->PrintLog("1. ���� 2. ��ų");
			G_UI->PrintLog("");
			std::cin >> playerSelect;

			if (playerSelect == 1) {
				G_UI->showLog();
				int damage = dmg(player, monster);
				monster.HP -= damage;

				//������ ���ݷ� ����
				player.lastDamage = damage;
				monster.hitDamage += damage;

				//���� +1 �� �ɷ�ġ ����
				player.addConcentration();
				break;
			}
			else if (playerSelect == 2) {
				if (player.useSkill(monster)) {
					continue;
				};
				break;
				//std::cout << "��ų�� ���� �̱���������" << std::endl;
			}
			/*else if (playerSelect == 3) {
				player.showPStat();
			}*/
			else {
				continue;
			}
		}
		if (monster.HP <= 0) {
			continue;
		}
		G_UI->PrintLog(monster.name, "�� ���� ü���� ", monster.HP);

		//���� ��
		G_UI->incrementLine(1);
		G_UI->moveCursorTo(0, G_UI->getLine());
		G_UI->PrintLog("��� ", monster.name, "�� ����!");
		Sleep(1000);
		// �������� �Ǻ�
		while (1) {
			if (auto bossPtr = dynamic_cast<Boss*>(&monster)) {
				int roll = (std::rand() % 100) + 1;
				if (roll <= 30) {
					// 60% Ȯ�� �Ϲ� ����
					G_UI->PrintLog( "��� " , monster.name , "�� �Ϲ� ����!");
					int damage = dmg(monster, player);
					// ƨ�ܳ��� ȿ��
					if (player.isReflecting) {
						damage = static_cast<int>(damage * 0.7);
						G_UI->PrintLog( "- ƨ�ܳ��� ȿ���� �������� ���ҵǾ����ϴ�! (", damage,")");
						player.isReflecting = false;
					}
					player.HP -= damage;
					player.hitDamage += damage;
				}
				else {
					// ��ų ���� (�����ϰ� �� ���� �� �ϳ�)
					
					int n = 3;
					int idx = rand() % n;
					if (idx == 0) {
						if (bossPtr->overturnFuture()) 
						{
							//G_UI->incrementLine(1);
							//G_UI->moveCursorTo(0, G_UI->getLine());
							//G_UI->PrintLog("�ٽú�����");
							//G_UI->moveCursorTo(0, G_UI->getLine());
							continue;
						}
						//G_UI->PrintLog("��� ", monster.name, "�� ��ų ����!");
						G_UI->PrintLog( "[��ų] �ʸ� �𸣴� �̾߱�");
						G_UI->moveCursorTo(0, G_UI->getLine());

					}
					else if (idx == 1) {
						if (bossPtr->heavensDoor(player)) 
						{
							//G_UI->incrementLine(1);
							//G_UI->moveCursorTo(0, G_UI->getLine());
							//G_UI->PrintLog("�ٽú�����");
							//G_UI->moveCursorTo(0, G_UI->getLine());
							continue;
						}
						//G_UI->PrintLog("��� ", monster.name, "�� ��ų ����!");
						G_UI->PrintLog("[��ų] �ʸ� �𸣴� �̾߱�");
						G_UI->moveCursorTo(0, G_UI->getLine());
					}
					else {
						if (bossPtr->otherworldlyBlade(player)) 
						{
							//G_UI->incrementLine(1);
							//G_UI->moveCursorTo(0, G_UI->getLine());
							//G_UI->PrintLog("�ٽú�����");
							//G_UI->moveCursorTo(0, G_UI->getLine());
							continue;
							continue;
						}
						//G_UI->PrintLog("��� ", monster.name, "�� ��ų ����!");
						G_UI->PrintLog("[��ų] �ʸ� �𸣴� �̾߱�");
						G_UI->moveCursorTo(0, G_UI->getLine());
					}
				}

				monster.MP += 2;


				
				if (!didselect && monster.HP <= 60) {
					int endingselect = 0;
					G_UI->PrintLog("����(???) : ��? �������� �� �ο��.. �̹� 'ȿ��'�� �Ѹ��������ٵ�..");
					G_UI->PrintLog( "            ��. ���� ���� �� ������ ������ �����ĺ��� �ʰھ�?");
					G_UI->PrintLog("��� : ���ڱ� ���� �Ҹ���?");
					G_UI->PrintLog("����(???) : �ʰ� �˰� �ʹٴ� ������ �˷��ٰ� ���� �� ��п� '��'�� Ǯ������");
					G_UI->PrintLog("�����ؾ��� �� ����.. ���� ���ڱ� �̷� ������ �ϴ� ������?");
					G_UI->PrintLog("1. �ڼ��� �̾߱⸦ ����. | 2. ���� ü���� ���� �ɵ鸮�°ų�!!!!");
					G_UI->PrintLog("");
					std::cin >> endingselect;
					if (endingselect == 1) {
						monster.Event_index = 7;
						Event(player, monster);
					}
					didselect = TRUE;
				}
				// ���� �� �� �ڵ� ȸ�� & �̷� ���� ȹ��
				bossPtr->regeneratePerTurn();

				//Ȯ�� �����ϰ� �Է¹޾ƾ� �Ѿ�� �ص� �׽�Ʈ��
				/*std::cin >> playerSelect;*/

				_getch();

				G_UI->RefreshStats();
				G_UI->showPstats(player.hitDamage);
				G_UI->showMstats(monster.hitDamage);
				G_UI->showLog();

				player.hitDamage = 0;
				monster.hitDamage = 0;

				break;
			}

			if (monster.Event_index == 7) {
				break;
			}
			else {
				// �Ϲ� ���ʹ� ������ �Ϲ� ����
				G_UI->PrintLog("��� ", monster.name , "�� ����!");
				int damage = dmg(monster, player);

				// ƨ�ܳ��� ȿ��
				if (player.isReflecting) {
					damage = static_cast<int>(damage * 0.7);
					G_UI->PrintLog("- ƨ�ܳ��� ȿ���� �������� ���ҵǾ����ϴ�! (", damage, ")");
					player.isReflecting = false;
				}
				player.HP -= damage;
				player.hitDamage += damage;

				//Ȯ�� �����ϰ� �Է¹޾ƾ� �Ѿ�� �ص� �׽�Ʈ��
				/*std::cin >> playerSelect;*/


				_getch();

				G_UI->RefreshStats();
				G_UI->showPstats(player.hitDamage);
				G_UI->showMstats(monster.hitDamage);
				G_UI->showLog();

				player.hitDamage = 0;
				monster.hitDamage = 0;

				break;
			}
		}
		
	}
	if (player.HP > 0) {
		if (monster.Event_index < 7) {
			G_UI->PrintLog( monster.name, "���� ���� �¸��ߴ�!" );
			G_UI->PrintLog("");
		}
		
		Sleep(1000);

		G_UI->RefreshStats();
		G_UI->showPstats(player.hitDamage);
		G_UI->showMstats(monster.hitDamage);
		G_UI->showLog();

		Event(player, monster);
	}
	else {
		G_UI->PrintLog("�й��ϰ� ���Ҵ�...");
		G_UI->PrintLog("");
		//�й� ����
		monster.Event_index = 8;
		Event(player, monster);
	}
}

int dmg(Actor attacker, Actor defender)
{
	int att = attacker.ATK;
	int def = defender.DEF;

	int damage = (att * 100) / (def + 100);
	G_UI->PrintLog( attacker.name , "��(��) " , defender.name , "���� " , damage , "��ŭ�� ���ظ� ������!");
	return damage;
}


void Event(Player& player, Monster& monster)
{
	G_UI->showLog();
	G_UI->PrintLog("");
	int playerSelect = 0;
	switch (monster.Event_index) {
	case 1:		//���ν�����
		G_UI->PrintLog("Event 1 <�� ���ν�����?>");
		G_UI->PrintLog("���� ? �� ���⿡ ������� �� �ν����Ⱑ ŭ��ŭ���ϰ� ������ �ֳ� ? ? ������ ?");
		G_UI->PrintLog("");
		G_UI->PrintLog("1.�׷� | 2. �� ���ƾ�? �̷� ���� �ִ� ��?");
		G_UI->PrintLog("");
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			G_UI->PrintLog("��� : �̷� ���� ������ ���� �ҽ�...? ���� �̰�... ������?(������ ȹ��)");
			player.addInventory(orange);
			G_UI->PrintLog( "��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog( "�÷��̾��� HP ", heal, " ��ŭ ȸ��!");

		}
		else if (playerSelect == 2) {
			G_UI->PrintLog( "��� : �ƴϾƴ� ��������� �̷��� ������ ���� �ν����Ⱑ ������ �������� ���ݾ�....?");
			G_UI->PrintLog("       �����ϰ� ����..? ���� ��..?");
			G_UI->PrintLog("���� : (�ƹ� �� ���� ����� ���� �� ��� ���𰡸� �㿩�ش�)");
			G_UI->PrintLog("��� : ���...? (��� ȹ��)");

			player.addInventory(apple);
			G_UI->PrintLog("��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("�÷��̾��� HP " , heal , " ��ŭ ȸ��!");
		}
		break;
	case 2:	// ������
		G_UI->PrintLog("Event 2 <�������� �Ϳ��� ������>");
		G_UI->PrintLog("���� �� �����Ӹ� �ִ°ž�? ������ ���� ���°ųİ�");
		G_UI->PrintLog("��? �� �������� �� Ư���ѵ� ������??");
		G_UI->PrintLog("");
		G_UI->PrintLog("1. �׷� ������ | 2. �ƴϾƴ� ���� �� �־�??");
		G_UI->PrintLog("");
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			G_UI->PrintLog("��� : ����!(���� Ȳ���� ����) �� �̸� �̳߰�?");
			G_UI->PrintLog("������ : (�̾����� ���𰡸� ����)");
			G_UI->PrintLog("��� : ��? �����̾�? ����..? ���� ���� ���� ������ΰ�?");
			G_UI->PrintLog("        ��� �� ������ž�?(���� ȹ��)");
			player.addInventory(grape);

			G_UI->PrintLog("��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("�÷��̾��� HP ", heal, " ��ŭ ȸ��!");
		}
		else if (playerSelect == 2) {
			G_UI->PrintLog("��� : �� �׷��� �����ε� ���� �԰� �ִٰ�.. ������ �߰ſ�! ���� �� ���̰� �Ǳ� �Ⱦ�!");
			G_UI->PrintLog("���� Ȳ���� �ڸ��� ���.");
			G_UI->PrintLog("���� ������ ���� �� ���𰡰� �ϴÿ��� ��������.");
			G_UI->PrintLog("��� : �ƾ�! ������? �ƺ�ī..��..? (�ƺ�ī�� ȹ��!)");
			player.addInventory(avocado);

			G_UI->PrintLog("��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("�÷��̾��� HP ", heal, " ��ŭ ȸ��!");
		}
		break;

	case 3: // �ֻ��
		G_UI->PrintLog("Event 3 <�ǹ��� �ֻ��>");
		G_UI->PrintLog("�̰� �� ����? ���ϴ� �ֻ�Ⱑ �� ���ּ����ϴµ�? ��¿��?");
		G_UI->PrintLog("");
		G_UI->PrintLog("1. ¯¯ ������ �� ������ ���� ��������. 2. �̷� ���� �ִ� �ֻ����? �翬�� �ȵ���");
		G_UI->PrintLog("");
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			G_UI->PrintLog("��� : (�ֻ��� ���� ������)��! �̰� ������? ��� �Ҵٸ� ���� �����̾���!");
			G_UI->PrintLog("       (�ֻ�Ⱑ ����ִ� ���ڿ� ���� ������) �� ���� �ִµ�? ��... �̹��� ��������....");
			player.addInventory(orange);

			G_UI->PrintLog("��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("�÷��̾��� HP ", heal, " ��ŭ ȸ��!");
		}
		else if (playerSelect == 2) {
			G_UI->PrintLog("�� �ָ����� ���𰡰� �����ϰ� �پ�´�.");
			G_UI->PrintLog("��� : ����.. �� ������ �� �ʳ�? �� ������");
			G_UI->PrintLog("       ��? �̰� �� ������ �شٰ�? �ʴ� ���� �뱤���ε� ����� �͵��� �� ������?");
			G_UI->PrintLog("       (���� ���� �ٰ�����)�̹��� �� �ֳ�? �� �����̳�... (������)��Ű ���~!");
			player.addInventory(watermelon);

			G_UI->PrintLog("��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("�÷��̾��� HP ", heal, " ��ŭ ȸ��!");
		}
		break;

	case 4: // ����ü
		G_UI->PrintLog("Event 4 <�ʵ� ����ü?>");
		G_UI->PrintLog("��� : �Ƿ��ϱ��� �������� �ʰ� ���� ���� ������ �� ����..");
		G_UI->PrintLog("�ڿ��� ���� �Ҹ��� ��� ���ƺ���");
		G_UI->PrintLog("XX : ��߻��!");
		G_UI->PrintLog("��� : ���� �ǰ��Ѱ���.... �� �̻��� �Ҹ��� �鸮��");
		G_UI->PrintLog("��... ������ ������ �������� �ߴµ� �ؼ��غ���?");
		G_UI->moveCursorTo(0, G_UI->getLine());
		G_UI->PrintLog("1. ���� �� ���� ��밡 �ȴ� 2. �� �߿��� ��⵵ �ƴϰ��� Į�� �̴´�");
		G_UI->PrintLog("");
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			G_UI->PrintLog("XX : ��߻��!");
			G_UI->PrintLog("��� : ����? ��¥ ��߻�߶�� ���Ѱſ��ݾ�!");
			G_UI->PrintLog("XX�� �ٰ������� �տ� ���𰡸� �������Ҵ�.");
			G_UI->PrintLog("��� : ������... ����� ���ƾ�... �� �����̾�...");
			G_UI->PrintLog("       �׷��׷�... ����.... (������ ȹ��)");
			player.addInventory(orange);

			G_UI->PrintLog("��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("�÷��̾��� HP ", heal, " ��ŭ ȸ��!");
		}
		else if (playerSelect == 2) {
			G_UI->PrintLog("��� : ������� �ϳ��� �𸣰ھ�! ��x��!");
			G_UI->PrintLog("��¦��¦�Ÿ��� ���𰡰� ��������.");
			G_UI->PrintLog("��� : �׷��׷� �̰͵� �����̳� ������ ���޾Ҿ�! ����� ��ģ ���̾�!(�ڸ�ȹ��)");
			player.addInventory(grapefruit);

			G_UI->PrintLog("��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("�÷��̾��� HP ", heal, " ��ŭ ȸ��!");
		}
		break;

	case 5: // ����
		G_UI->PrintLog("�̺�Ʈ BOSS <���������� '��'�̵� �̾߱�>");
		G_UI->PrintLog("����(???) : �׷��� ������ �ٴϴ°� ��̾�?");
		G_UI->PrintLog("            �� �ٺ���? ��... �װ� �� ����ε� ���ٰ� �ֿ��°ž�?");
		G_UI->PrintLog("            �� �̻� ���� ������ �����ϴ°� �����ž�. �� ȣ��ȣ������ �ʴٰ�");
		Sleep(2000);
		G_UI->PrintLog("��� : ���۽������� �������� ȭ�� �ٷ� �غ� �ؾ��� �� ����.");
		G_UI->PrintLog(player.name, " (��)�� ������ ����� Į�� �����");
		G_UI->PrintLog("������ ��������....!");
		Sleep(2000);
		break;

	case 6: // ����
		G_UI->clearALL();
		G_UI->PrintLog("<NORMAL����> �ٽö�� ����");
		Sleep(2000);
		G_UI->PrintLog("���ฦ �����߸� �� ���� ���� ������ ���ư� ���ฦ ó���ߴٴ� �ҽ��� ���ߴ�.");
		G_UI->PrintLog("���ô� ��ĥ�� ���������� �����ʾ� �� ������������....");
		Sleep(1000);
		G_UI->PrintLog("��� : ����ó�� ��мҴٵ� �ٽ��ȱ� �����߰�, ���� �������ž�...");
		G_UI->PrintLog("       �׷��� ���̸� ���ϰ� ������ ������ ��°ɱ�..?");
		Sleep(2000);
		exit(1);
		break;
	case 7:
		G_UI->PrintTrueEnd();

		exit(1);
	case 8:
		G_UI->PrintLog( "����... ���⼭ ���� �� ����... ��мҴ��� ������ �����ľ�..��.!" );
		G_UI->PrintLog( "�ٽ� �����غ���");
		exit(1);
	default:
		break;
	}
	Sleep(1000);
}

void afterBattle(Player& player)
{
	G_UI->PrintLog( "���� ������ �ö󰡴� ����� ���δ�!");
	int playerSelect = 0;
	
	while (1) {
		G_UI->PrintLog("");
		G_UI->PrintLog( "1. �ö󰣴� 2. �ָӴϸ� Ȯ���Ѵ� 3.������� �����.");
		G_UI->PrintLog("");
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			G_UI->PrintLog( player.name , "��(��) ������ ���ٵ�� ���� ������ ���ߴ�.");
			Sleep(1000);
			break;
		}
		else if (playerSelect == 2) {
			player.showInventory();
			Sleep(1000);
		}
		else if (playerSelect == 3) {
			G_UI->showLog();
			G_UI->PrintLog("");
			int fruitSelect1 = 0;
			int fruitSelect2 = 0;
			G_UI->PrintLog( "���� ���Ϸ� �����?");
			G_UI->PrintLog("");
			player.showInventory();
			G_UI->PrintLog("");
			//std::cout << player.fruit_inventory.size() << std::endl;
			std::cin >> fruitSelect1;
			if (fruitSelect1 > player.fruit_inventory.size()) {
				G_UI->PrintLog( "������ ���� �ʴ� �� ����..." );
				Sleep(1000);
				G_UI->showLog();
				continue;
			}
			std::cin >> fruitSelect2;
			if (fruitSelect1 == fruitSelect2) {
				G_UI->PrintLog( "�̹� ������ �����̴�..." );
				Sleep(1000);
				G_UI->showLog();
				continue;
			}
			if (fruitSelect2 > player.fruit_inventory.size()) {
				G_UI->PrintLog( "������ ���� �ʴ� �� ����..." );
				Sleep(1000);
				G_UI->showLog();
				continue;
			}
			G_UI->PrintLog( player.fruit_inventory[fruitSelect1 - 1].name , "��(��)" , player.fruit_inventory[fruitSelect2 - 1].name , "��(��) ����ؼ� ���Ḧ �����?");
			G_UI->PrintLog("1. ���� ������! 2. �ٽ� �����غ���");
			G_UI->PrintLog("");
			std::cin >> playerSelect;
			if (playerSelect == 1) {
				player.blendFruit(player.fruit_inventory[fruitSelect1 - 1], player.fruit_inventory[fruitSelect2 - 1]);
				Sleep(3000);
			}
			else {
				Sleep(1000);
				G_UI->showLog();
				continue;
			}
		}
		/*else if (playerSelect == 4) {
			player.showPStat();
		}*/
		else {
			continue;
		}
	}
}

void GAME(Player& player, const std::map<int, Monster*>& monsterMap)
{
	for (auto it = monsterMap.begin(); it != monsterMap.end(); ++it) 
	{
		Monster* mptr = it->second;

		delete G_UI;
		G_UI = new UIManager(&player, &*mptr);

		if (G_UI == NULL)
		{
			std::cout << "���� �߻� G_UI�� �������͸� ����Ŵ";
			std::abort();
		}

		G_UI->clearALL();
		G_UI->RefreshScreen();

		Battle(player, *mptr);

		Sleep(3000);
		G_UI->clearALL();
		G_UI->RefreshScreen();

		afterBattle(player);
	}
}
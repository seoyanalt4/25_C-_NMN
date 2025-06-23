#include "UIManager.h"
#include <windows.h>
#include <iostream>
#include <iomanip>

//���� �ڵ� ���ǻ��� ui �����ġ�� ���δ� �����ͷ� �������̶� �ٳѱ������� ���� ���ɼ��� ������ ���� ����!
//Ŀ���̵� ��Ű�¾� public ���� ���ξ����� �̿����ֽø� �����ϰڽ��ϴ�.
//(0,0) ~ (��100,9) ������ ��� �÷��̾� ���� ui ����
//(0,10) ���� ���丮�� ��Ÿ �α� ������ ���մµ� �ʿ�� ����

UIManager::UIManager(Player* p, Monster* m) : player(p), monster(m) {}

//������ �ڸ��� ī���� 
int UIManager::DigitCount(int num)
{
    return std::to_string(num).length();
}


//���� �Լ��� ���� �Լ�(private)�� �Ʒ��� ������� �� �Լ���


//Ŀ�� �̵��Լ�
void UIManager::moveCursorTo(int x, int y)
{
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Ŀ�� �� ��ġ ����
void UIManager::setLine(int line) {
    if (line >= 0) {
        Current_Line = line;
    }
}

// �� ��ġ ��������
int UIManager::getLine() const {
    return Current_Line;
}

// �� ��ġ ����
void UIManager::incrementLine(int delta) {
    Current_Line += delta;
    if (Current_Line > 99) Current_Line = 99; // ȭ�� ���� ���
}

// �� ��ġ ����
void UIManager::decrementLine(int delta) {
    Current_Line -= delta;
    if (Current_Line < 0) Current_Line = 0;
}
//��ܺ� ���Ž��Ѽ� �����ִ� �Լ�
void UIManager::RefreshStats()
{
    clearP();
    clearM();
    showPstats();
    showMstats();
}

//�÷��̾�ĭ ����� �Լ�
void UIManager::clearP()
{
    for (int j = 0; j < 9; j++)
    {
        moveCursorTo(0, 0 + j);
        std::cout << "                                                ";
    }
}

//����ĭ ����� �Լ�
void UIManager::clearM()
{
    for (int j = 0; j < 9; j++)
    {
        moveCursorTo(50, 0 + j);
        std::cout << "                                                ";
    }
}

//�α�â ���� �� ����� �Լ�
void UIManager::clearALL()
{
    for (int j = 0; j < 100; j++)
    {
        moveCursorTo(0, 0 + j);
        std::cout << "                                                                                                                                                                                                         ";
    }
    moveCursorTo(0, 0);
    Current_Line = 0;
}


//�÷��̾� ���� �����ִ� �Լ�
void UIManager::showPstats()
{
    for (int j = 0; j < 6; j++) // �÷��̾� �ڽ������� ����� (����ĭ�� �� �������� ����)
    {
        moveCursorTo(0, 0 + j);
        std::cout << "                                                ";
    }

    for (int j = 0; j < 9; j++)
    {
        moveCursorTo(0, 0 + j);

        if (j == 0) { std::cout << "�������������� �÷��̾��� ���� ��������������     "; }
        if (j == 1) { std::cout << "���̸�: " << player->name << std::setw(25 + 0 - player->name.length()) << "��"; }
        if (j == 2) { std::cout << "��HP: " << player->HP << std::setw(25 + 2 - DigitCount(player->HP)) << "��"; }
        if (j == 3) { std::cout << "��MP: " << player->MP << std::setw(25 + 2 - DigitCount(player->MP)) << "��"; }
        if (j == 4) { std::cout << "��ATK: " << player->ATK << std::setw(25 + 1 - DigitCount(player->ATK)) << "��"; }
        if (j == 5) { std::cout << "��DEF: " << player->DEF << std::setw(25 + 1 - DigitCount(player->DEF)) << "��"; }
        if (j == 6) { std::cout << "������: " << player->concentration << std::setw(25 + 0 - DigitCount(player->concentration)) << "��"; }
        if (j == 7) { std::cout << "��������������������������������������������������������������"; }
        if (j == 8) { std::cout << " "; }
        
    }
}

//���� ���� �����ִ� �Լ�
void UIManager::showMstats()
{
    for (int j = 0; j < 6; j++)// ���� �ڽ������� ����� (����ĭ�� �� �������� ����)
    {
        moveCursorTo(50, 0 + j);
        std::cout << "                                                ";
    }

    if (monster->HP < 0) { return; } //���� ������ �ڽ� ��� X

    if (monster->name == "����")
    {
        for (int j = 0; j < 9; j++)
        {
            moveCursorTo(50, 0 + j);
            if (j == 0) { std::cout << "�������������� �������� ���� ��������������     "; }
            if (j == 1) { std::cout << "���̸�: " << monster->name << std::setw(25 + 0 - monster->name.length()) << "��"; }
            if (j == 2) { std::cout << "��HP: " << monster->HP << std::setw(25 + 2 - DigitCount(monster->HP)) << "��"; }
            if (j == 3) { std::cout << "��MP: " << monster->MP << std::setw(25 + 2 - DigitCount(monster->MP)) << "��"; }
            if (j == 4) { std::cout << "��ATK: " << monster->ATK << std::setw(25 + 1 - DigitCount(monster->ATK)) << "��"; }
            if (j == 5) { std::cout << "��DEF: " << monster->DEF << std::setw(25 + 1 - DigitCount(monster->DEF)) << "��"; }
            if (j == 6) { std::cout << "���̷�: " << monster->Get_Stack() << std::setw(25 + 0 - DigitCount(monster->Get_Stack())) << "��"; }
            if (j == 7) { std::cout << "��������������������������������������������������������������"; }
            if (j == 8) { std::cout << " "; }
        }
    }
    else
    {
        for (int j = 0; j < 9; j++)
        {
            moveCursorTo(50, 0 + j);
            if (j == 0) { std::cout << "�������������� �������� ���� ��������������     "; }
            if (j == 1) { std::cout << "���̸�: " << monster->name << std::setw(25 + 0 - monster->name.length()) << "��"; }
            if (j == 2) { std::cout << "��HP: " << monster->HP << std::setw(25 + 2 - DigitCount(monster->HP)) << "��"; }
            if (j == 3) { std::cout << "��MP: " << monster->MP << std::setw(25 + 2 - DigitCount(monster->MP)) << "��"; }
            if (j == 4) { std::cout << "��ATK: " << monster->ATK << std::setw(25 + 1 - DigitCount(monster->ATK)) << "��"; }
            if (j == 5) { std::cout << "��DEF: " << monster->DEF << std::setw(25 + 1 - DigitCount(monster->DEF)) << "��"; }
            if (j == 6) { std::cout << "��"<<std::setw(31) << "��"; }
            if (j == 7) { std::cout << "��������������������������������������������������������������"; }
            if (j == 8) { std::cout << " "; }
        }
    }
}

//�Լ� �����ε� �Ἥ �������� ������ hp���� ����
void UIManager::showPstats(int dmg)
{
    if (player->hitDamage <= 0) return;
    moveCursorTo(0, 2);
    std::cout << "��HP: " << player->HP << std::setw(5) << "(-" << dmg << ")" << std::setw(20 + 1 - DigitCount(player->HP) - DigitCount(dmg)) << "��";
}

void UIManager::showMstats(int dmg)
{
    if (monster->HP < 0) return;
    if (monster->hitDamage <= 0) return;
    moveCursorTo(50, 2);
    std::cout << "��HP: " << monster->HP << std::setw(5) << "(-" << dmg << ")" << std::setw(20 + 1 - DigitCount(monster->HP) - DigitCount(dmg)) << "��";
}



//�α�â ������ �α�â ��ġ�� Ŀ�� �̵��ϴ� �Լ�
void UIManager::showLog()
{
    for (int j = 0; j < 30; j++)
    {
        moveCursorTo(0, 10 + j);
        std::cout << "                                                                                                              ";
    }
    moveCursorTo(0, 10);
    Current_Line = 10;
}

//ȭ�鰻��
void UIManager::RefreshScreen()
{
    RefreshStats();
    showLog();
}

//�ؽ�Ʈ�� ���
void UIManager::PrintLog(const std::string& log) 
{
    if (Current_Line > 30)
    {
        Current_Line = 10;
        showLog();
    }
    moveCursorTo(0, Current_Line++);
    std::cout << log;
}

//Ÿ��Ʋ ���
void UIManager::PrintTitle()
{
    for (int j = 0; j < 12; j++)
    {
        moveCursorTo(30, 5 + j);
        if (j == 0) { std::cout << "��������������������������������������������������������������������������������������������������������������     "; }
        if (j == 1) { std::cout <<"��"<<std::setw(55) << "��"; }
        if (j == 2) { std::cout << "��"<<std::setw(55) << "��"; }
        if (j == 3) { std::cout << "��" << std::setw(40) << "���� �� ��мҴٿ� �� ����?" << std::setw(15) << "��";}
        if (j == 4) { std::cout << "��" << std::setw(55) << "��";}
        if (j == 5) { std::cout << "��" << std::setw(27) << "TEAM: �ڸ��Ҵ�" << std::setw(28) << "��";; }
        if (j == 6) { std::cout << "��" << std::setw(55) << "��";}
        if (j == 7) { std::cout << "��������������������������������������������������������������������������������������������������������������"; }
        if (j == 8) { std::cout << " "; }
        if (j == 11) { std::cout << std::setw(20) << "������ �Է����ּ��� : "; }
       

    }
}

//��Ʈ�ζ� Ʈ�翣�� ����а�
void UIManager::PrintIntro()
{
    clearALL();
    PrintLog("<���ѷα�>");
    Sleep(500);
    PrintLog("���к��� ������ ������ ���� <�����>");
    Sleep(500);
    PrintLog("�װ��� ���� ��� �Ҵٴ� ������ ������ �θ� ��翡�Դ� �Ϸ縦 ��ư��� ������ ���̾���.");
    Sleep(500);
    PrintLog("��� : (�� ������)���Ҿ�, ���õ� ��ư������� ��� �Ҵ� �� ���Ϸ� ������~");
    Sleep(500);
    PrintLog("������ �Ÿ��� �ȴ� �� ���� �긻�� �Ѹ���");
    Sleep(500);
    PrintLog("<��� �Ҵ� �Ͻ� ǰ��>");
    Sleep(500);
    PrintLog("��� : �����? ��...��..ǰ..��? �̰� ���� ����� ������ݾ�!");
    Sleep(500);
    PrintLog("(���� �ȿ��� �Ļ��ϰ� �ִ� �� �䳢 ���ο��� ���� �Ǵ�) �̺�, �� ���ڱ� ����� ��������?");
    Sleep(500);
    PrintLog("�䳢 ���� : ���� ����, ������ �鸮�� �ҹ��� ���ϸ� ���� ��ó ������ �����ϰ� �ִ� ���డ ��� �翡�ٰ� ���� Ǯ������.");
    Sleep(500);
    PrintLog("            �ñ��ϸ� ���� ����� ���� (����� ���� �Դ´�)");
    Sleep(500);
    PrintLog("��� : ��, ����� �������� �׷� ���簡 ��ó�� �־�������?");
    Sleep(500);
    PrintLog("       ���� �̷��� �а��ߴ���? (�Ѽ��� ����) ���� Ȯ���� �غ��߰ھ�.");
    Sleep(500);
    PrintLog("       �����ڰ� �������� �����̴�.");
    Sleep(6000);

    clearALL();

    PrintLog("<���� ��ε�>");
    Sleep(500);
    PrintLog("��� : ���� ��......��.....?? ���Ⱑ ������ ���̶��? ����� ž ���� ���ܸԾ���.");
    Sleep(500);
    PrintLog("         �����Ⱑ �Ȼ��ݾ�..... ��, �ϴ� ����...");
    Sleep(500);
    PrintLog("ž�� ������ ���� �� �ҳ��� �Ƿ翧�� ž ���� ��������.");
    Sleep(500);
    PrintLog("��� : ���� �̰�?");
    Sleep(500);
    PrintLog("XX : ���� �Ϸ� �°ž�?");
    Sleep(500);
    PrintLog("��� : Ȥ��, ���⿡ ��� ���༼��?");
    Sleep(500);
    PrintLog("����(???) : ��.... ���� �׷��� �ڴ�� �θ��°Ű�... �����?");
    Sleep(500);
    PrintLog("��� : ��, ��� ���డ ��� �翡�ٰ� ���� �����ߴٰ� �� �� ����(����)������ �Ծ�.");
    Sleep(500);
    PrintLog("����(???) : �׷��ٸ�?");
    Sleep(500);
    PrintLog("��� : ������ �ð��� ������ �� �ž�...");
    Sleep(500);
    PrintLog("����(???) : �ƹ��͵� �𸣴ϱ� �׷��� ������ ���� �ִ°ž�.");
    Sleep(500);
    PrintLog("��� : ����~~? ? �󱼺��� �������~");
    Sleep(500);
    PrintLog("���� �����Ѵ�.");
    Sleep(500);
    PrintLog("��� : ���� ��¥ �� ��� �Ÿ��� ���̳�...");
    Sleep(5000);
}

void UIManager::PrintTrueEnd()
{
    clearALL();
    PrintLog("<TRUE����> �˴� ��, �˰Ե� ��");
    Sleep(1500);
    PrintLog("������ ���� �츮�� ���� ���� ���� ž ������ ���Դ�.");
    PrintLog("ž ������ ���� ���� ������ ���� ������ ��⸦ �����Եȴ�.");
    PrintLog("���� ����κ��� '���'�̶�� ��¥ �ǹ̸� ��� �Ǿ���.");
    Sleep(1500);
    PrintLog("������Ʈ <MELON>");
    Sleep(500);
    PrintLog("Maximum �ִ���");
    Sleep(500);
    PrintLog("Energy ��������");
    Sleep(500);
    PrintLog("Live �츮��");
    Sleep(500);
    PrintLog("ON switch ����");
    Sleep(500);
    PrintLog("��, ���� �ڿ��� ���� ����");
    Sleep(500);
    PrintLog("�װ��� ������Ʈ �̸��� �°� ����̶�� ������ �Ű�ü�� ����ƿ� '��'�� �Ѹ��� �ִ� ���̴�.");
    Sleep(500);
    PrintLog("��� : (�Ӹ��� �θ޸�)�̷�.. ���� �׷��ſ���.. �� �����ϴ� �ɷµ� �������� ������");
    Sleep(1000);
    PrintLog("����(???) : �� ��� ��������. ���� �� ���ô� ����� �����Ѱ� �¾�.");
    PrintLog("            ������ ����� �鿩���� �������� � �����簡 ���⿡ ������ ģ����.");
    PrintLog("            �ٷ� ��п� ������ ��� ������ �ɾ� �����ž�.");
    PrintLog("            �� ������ ���κ��� ������ �ݼ���� �������� ���� ���� �����̿���.");
    PrintLog("            ���� ȥ�� �Ҿ�־� �װ� �Ű�ü�� �Ǿ� ������ Ÿ��Ÿ�� �� ��ȥ�� ����Ѵ�.");
    PrintLog("            �̰� ���� �԰� �ִ� ����� �����̾�.");
    PrintLog("            �� �������δ� �� ���ø� �ٲ� ���� ����.");
    PrintLog("            ������ �� ���� �Ƿ��� �Ǵ� ����� ��Ÿ���ٴ� �ſ� �ٽ� ����� ������ �Ǿ���");
    PrintLog("            (�̼�������)���� �ʶ� ������ ���θ� �ĵ��ž� �غ�ƾ�?");
    Sleep(3000);
    PrintLog("��� : (Į�� �����ϸ�)����� ������... ���� ����� �׷� �Ű�ü�� ���ٴ� �뼭����! ����!");
    Sleep(1000);
    PrintLog("������ �޸鿡 ������ ������ �ٽ� �����̷��� �Ѵ�.");
    Sleep(1500);
    PrintLog("���� ��� ������ ��� ������ ����ĥ �� ���� ���ΰ�???");
    Sleep(2000);

}

//���ϰ� ����ϱ� ���� ���� ������
UIManager* G_UI = nullptr; 



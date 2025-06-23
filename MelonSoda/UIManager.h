#pragma once
#include <iostream>
#include "Player.h"
#include "Monster.h"

class UIManager {
private:
    Player* player;
    Monster* monster;

    //������ �ڸ��� ���� �Լ�
    int DigitCount(int num);

    //���� ����ϰ� �ִ� ��
    int Current_Line = 0;

public:
    UIManager(Player* p, Monster* m);

    // �� ��ġ ����
    void setLine(int line);

    // �� ��ġ ��������
    int getLine() const;

    //�� ��ġ ����
    void incrementLine(int delta = 1);
    void decrementLine(int delta = 1);

    //Ŀ�� ��ġ �̵���Ű�� �Լ�
    void moveCursorTo(int x, int y);

    //�÷��̾� �ڽ� �ʱ�ȭ�� ��� �Լ�
    void showPstats();
    //���� �ڽ� �ʱ�ȭ�� ��� �Լ�
    void showMstats();

    //�Լ� �����ε� �̿��ؼ� ü���ٸ� ���Ž�Ű�� �Լ�
    //�÷��̾�
    void showPstats(int dmg);
    //����
    void showMstats(int dmg);

    //ȭ�� ������������ �Լ�
    void clearALL();
    //�÷��̾� �ڽ� ����� �Լ�
    void clearP();
    //�÷��̾� �ڽ� ����� �Լ�
    void clearM();

    //��ܺ� ���� ����� �����ִ� �Լ�
    void RefreshStats();
    //�ϴܺ� �α� ����� �Լ�
    void showLog();
    //���� �ΰ� ���ĳ��� �Լ�
    void RefreshScreen();

    //�α� ����ϴ� �Լ��� ���ø�ȭ + ���ڼ��� �����ε�
    // ��� �����ϸ� 5�� 6������ ���� ����
    //1.�Ϲ� �ؽ�Ʈ�� ��� (1���� ��ǻ� �̰�츸 �ҵ�)
    void PrintLog(const std::string& log);
    //2. 2��¥�� ���
    template<typename T1, typename T2>
    void PrintLog(T1 a, T2 b);
    //3. 3��¥�� ���
    template<typename T1, typename T2, typename T3>
    void PrintLog(T1 a, T2 b, T3 c);
    //4. 4��¥�� ���
    template<typename T1, typename T2, typename T3, typename T4>
    void PrintLog(T1 a, T2 b, T3 c, T4 d);
    //5.  5��¥�� ���
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    void PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e);
    //6.  6��¥�� ���
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    void PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e, T6 f);
    //7.  7��¥�� ���
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    void PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e, T6 f, T7 g);

    //Ÿ��Ʋ ���
    void PrintTitle();
    //��Ʈ�� ���
    void PrintIntro();
    //Ʈ�翣�� ���
    void PrintTrueEnd();
};

//���⿡ �Լ����Ǹ� ���ϸ� �������� 
//�� �밡�ٷ� 7������ �����ߴµ� �� ���� ��� ������ �������ּŵ� �˴ϴ�.
//���� �� ���� ����� �𸣰پ��

//2. 2��¥�� ����
template<typename T1, typename T2>
void UIManager::PrintLog(T1 a, T2 b) 
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}

//3. 3��¥�� ����
template<typename T1, typename T2, typename T3>
void UIManager::PrintLog(T1 a, T2 b, T3 c) 
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b << c;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}

//4. 4��¥�� ����
template<typename T1, typename T2, typename T3, typename T4>
void UIManager::PrintLog(T1 a, T2 b, T3 c, T4 d) 
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b << c << d;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}

//5. 5��¥�� ����
template<typename T1, typename T2, typename T3, typename T4, typename T5>
void UIManager::PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e) 
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b << c << d << e;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}

//6. 6��¥�� ����
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
void UIManager::PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e, T6 f) 
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b << c << d << e<< f;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}

//7. 7��¥�� ����
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
void UIManager::PrintLog(T1 a, T2 b, T3 c, T4 d, T5 e, T6 f, T7 g)
{
    moveCursorTo(0, Current_Line++);
    std::cout << a << b << c << d << e << f << g;
    if (Current_Line > 40) {
        Current_Line = 10;
        showLog();
    }
}


//���� ������ ����
extern UIManager* G_UI;
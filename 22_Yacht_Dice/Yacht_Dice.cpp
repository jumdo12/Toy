#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <stdint.h>
#include <random>

#define False 0
#define True 1

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32

using namespace std;

void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void MakeBasedLine()
{
    for (int i = 1; i <= 57; i++)
    {
        gotoxy(i, 0);
        cout << "=";
        gotoxy(i, 28);
        cout << "=";
    }
}
void DrawGameMenu();
void MenuSelect(int cnt);

void EndGame()
{
    MakeBasedLine();
    gotoxy(25, 14);
    cout << "게임을 종료합니다 !";
    gotoxy(0, 25);
    return;
}

int CalcScore(int cnt1, int Dice[], int DiceNumCnt[])
{
    int tmp=0 , ans=0 , cnt = 0;
    int is2 = 0, is3 = 0 , sum=0;
    int is4 = 0, is1 = 0;
    int sm1;

    switch (cnt1)
    {
    case 0:
        return 1 * DiceNumCnt[0];
    case 1:
        return  (2 * DiceNumCnt[1]);
    case 2:
        return  3 * DiceNumCnt[2];
    case 3:
        return  4 * DiceNumCnt[3];
    case 4:
        return  5 * DiceNumCnt[4];
    case 5:
        return  6 * DiceNumCnt[5];
    case 6: //Choice
        for (int i = 0; i < 6; i++)
        {
            if (DiceNumCnt[i])
            {
                ans += DiceNumCnt[i] * (i+1);
            }
        }
        return ans;
    case 7: //4 of Kind
        for (int i = 0; i < 6; i++)
        {
            if (DiceNumCnt[i] == 4)
            {
                sum += 4 * (i + 1);
                is4 = 1;
            }
            if (DiceNumCnt[i] == 1)
            {
                sum += (i + 1);
                is1 = 1;
            }
        }
        if (is4 == 1 && is1 == 1)
        {
            return sum;
        }
        return 0;
    case 8: //Full House

        for (int i = 0; i < 6; i++)
        {
            if (DiceNumCnt[i] == 2)
            {
                is2 = 1;
                sum += 2 * (i+1);
            }
            if (DiceNumCnt[i] == 3)
            {
                is3 = 1;
                sum += 3 * (i + 1);
            }
        }
        if (is2 == 1 && is3 == 1)
        {
            return sum;
        }
        return 0;
    case 9:    //S. Straight
        for (int i = 0; i < 6; i++)
        {
            if (DiceNumCnt[i] == 0)
            {
                sm1 = i;
                cnt++;
            }
        }
        if (cnt == 1)
        {
            return 15;
        }
        else if (cnt == 2)
        {
            if (sm1 == 5)
            {
                if (DiceNumCnt[0] == 0)
                {
                    return 15;
                }
            }
            if (DiceNumCnt[sm1 - 1] == 0)
            {
                return 15;
            }
        }
        return 0;
    case 10:    // L. Straight
        for (int i = 0; i < 6; i++)
        {
            if (DiceNumCnt[i] == 0)
            {
                cnt++;
            }
        }
        if (cnt == 1)
        {
            return 30;
        }
        return 0;
    case 11:    //Yacht :
        for (int i = 0; i < 6; i++)
        {
            if (DiceNumCnt[i] == 5)
            {
                return 50;
            }
        }
        return 0;
    }
}
void DiceRoll(int Dice[], int DiceNumCnt[], int Score[], int checked[])
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 6);

    for (int i = 0; i < 6; i++) //초기화
    {
        DiceNumCnt[i] = 0;
    }

    for (int i = 0; i < 5; i++)
    {
        if (!checked[i])
        {
            Dice[i] = dis(gen);
        }
        DiceNumCnt[Dice[i]-1]++;
    }
}

void ShowDice(int Dice[])
{
    for (int i = 0; i < 5; i++)
    {
        switch (Dice[i])
        {
        case 1:
            gotoxy(35 + 4*i, 9);
            cout << "*";
            break;
        case 2:
            gotoxy(34 + 4 * i, 8);
            cout << "*";
            gotoxy(36 + 4 * i, 10);
            cout << "*";
            break;
        case 3:
            gotoxy(35 + 4 * i, 9);
            cout << "*";
            gotoxy(34 + 4 * i, 8);
            cout << "*";
            gotoxy(36 + 4 * i, 10);
            cout << "*";
            break;
        case 4:
            gotoxy(34 + 4 * i, 8);
            cout << "*";
            gotoxy(36 + 4 * i, 8);
            cout << "*";
            gotoxy(34 + 4 * i, 10);
            cout << "*";
            gotoxy(36 + 4 * i, 10);
            cout << "*";
            break;
        case 5:
            gotoxy(35 + 4 * i, 9);
            cout << "*";
            gotoxy(34 + 4 * i, 8);
            cout << "*";
            gotoxy(36 + 4 * i, 8);
            cout << "*";
            gotoxy(34 + 4 * i, 10);
            cout << "*";
            gotoxy(36 + 4 * i, 10);
            cout << "*";
            break;
        case 6:
            gotoxy(34 + 4 * i, 8);
            cout << "*";
            gotoxy(36 + 4 * i, 8);
            cout << "*";
            gotoxy(34 + 4 * i, 9);
            cout << "*";
            gotoxy(36 + 4 * i, 9);
            cout << "*";
            gotoxy(34 + 4 * i, 10);
            cout << "*";
            gotoxy(36 + 4 * i, 10);
            cout << "*";
            break;
        }
    }
}
int TotalScore(int Score[])
{
    int sum = 0;

    for (int i = 0; i < 14; i++)
    {
        if (Score[i] != -1)
        {
            sum += Score[i];
        }
    }
    return sum;
}
void endgame(int Score[])
{
    system("cls");
    gotoxy(25, 12);
    cout << "게임 종료";
    gotoxy(25, 15);
    cout << "최종 점수 : " << TotalScore(Score);
    gotoxy(1, 27);
    while (!(_kbhit()))
    {
        gotoxy(3, 4);
        cout << " ";
    }
}
int Subtotal(int Score[])
{
    int sum = 0;
    for (int i = 0; i < 6; i++)
    {
        if (Score[i] != -1)
        {
            sum += Score[i];
        }
    }
    if (sum >= 63)
    {
        Score[13] = 35;
    }
    else
    {
        return sum;
    }
}
void ShowPreScore(int Dice[] , int DiceNumCnt[] , int Score[])
{
    for (int i = 0; i < 12; i++)
    {
        if (i < 6) {
            gotoxy(7, 2 * i + 1);
            cout << "  ";
            gotoxy(6, 2 * i + 1);
            cout << "  ";
            cout << CalcScore(i, Dice, DiceNumCnt);
        }
        else
        {
            gotoxy(7, 2 * i + 3);
            cout << "  ";
            gotoxy(6, 2 * i + 3);
            cout << "  ";
            cout << CalcScore(i, Dice, DiceNumCnt);
        }
    }
}
void EraseDice(int Dice[])
{
    for (int i = 0; i < 5; i++)
    {
        switch (Dice[i])
        {
        case 1:
            gotoxy(35 + 4 * i, 9);
            cout << " ";
            break;
        case 2:
            gotoxy(34 + 4 * i, 8);
            cout << " ";
            gotoxy(36 + 4 * i, 10);
            cout << " ";
            break;
        case 3:
            gotoxy(35 + 4 * i, 9);
            cout << " ";
            gotoxy(34 + 4 * i, 8);
            cout << " ";
            gotoxy(36 + 4 * i, 10);
            cout << " ";
            break;
        case 4:
            gotoxy(34 + 4 * i, 8);
            cout << " ";
            gotoxy(36 + 4 * i, 8);
            cout << " ";
            gotoxy(34 + 4 * i, 10);
            cout << " ";
            gotoxy(36 + 4 * i, 10);
            cout << " ";
            break;
        case 5:
            gotoxy(35 + 4 * i, 9);
            cout << " ";
            gotoxy(34 + 4 * i, 8);
            cout << " ";
            gotoxy(36 + 4 * i, 8);
            cout << " ";
            gotoxy(34 + 4 * i, 10);
            cout << " ";
            gotoxy(36 + 4 * i, 10);
            cout << " ";
            break;
        case 6:
            gotoxy(34 + 4 * i, 8);
            cout << " ";
            gotoxy(36 + 4 * i, 8);
            cout << " ";
            gotoxy(34 + 4 * i, 9);
            cout << " ";
            gotoxy(36 + 4 * i, 9);
            cout << " ";
            gotoxy(34 + 4 * i, 10);
            cout << " ";
            gotoxy(36 + 4 * i, 10);
            cout << " ";
            break;
        }
    }
}
void StartGameDraw()
{
    system("cls");
    MakeBasedLine();

    gotoxy(1, 1);
    cout << "Aces : ";
    gotoxy(1, 3);
    cout << "Deuces : ";
    gotoxy(1, 5);
    cout << "Threes : ";
    gotoxy(1, 7);
    cout << "Fours : ";
    gotoxy(1, 9);
    cout << "Fives : ";
    gotoxy(1, 11);
    cout << "Sixex : ";
    gotoxy(1, 13);
    cout << "Subtotal : ";
    gotoxy(10, 13);
    cout << "/ 63";

    gotoxy(1, 15);
    cout << "Choice : ";
    gotoxy(1, 17);
    cout << "4 of Kind : ";
    gotoxy(1, 19);
    cout << "Full House : ";
    gotoxy(1, 21);
    cout << "S. Straight : ";
    gotoxy(1, 23);
    cout << "L. Straight : ";
    gotoxy(1, 25);
    cout << "Yacht : ";

    gotoxy(1, 27);
    cout << "Total : ";

    gotoxy(38, 23);
    cout << "Roll";
    gotoxy(38 + 9, 23);
    cout << "남은 횟수 : ";
}
void StartErasePoint(int col1, int col2 ,int cnt1,int cnt2)
{
    if (col1)
    {
        if (cnt2)
        {
            gotoxy(41, 23);
            cout << "  ";
        }
        else
        {
            gotoxy(35 + 4 * col2, 12);
            cout << "  ";

        }
    }
    else
    {
        if (cnt1 < 6)
        {
            gotoxy(11, 2 * cnt1 + 1);
            cout << "  ";
        }
        else
        {
            gotoxy(11, 2 * cnt1 + 3);
            cout << "  ";
        }
    }
}
void StartSetPoint(int col1, int col2, int cnt1, int cnt2)
{
    if (col1)
    {
        if (cnt2)
        {
            gotoxy(41, 23);
            cout << "ㅇ";
        }
        else
        {
            gotoxy(35 + 4 * col2, 12);
            cout << "ㅇ";
        }
    }
    else
    {
        if (cnt1 < 6)
        {
            gotoxy(11, 2 * cnt1 + 1);
            cout << "ㅇ";
        }
        else
        {
            gotoxy(11, 2 * cnt1 + 3);
            cout << "ㅇ";
        }
    }
}
void ShowCount(int count[])
{
    gotoxy(40 + 9 + 3, 23);
    cout << "  ";
    cout << count[0];
}
void StartSelct(int col1, int col2,int cnt1, int cnt2 , int Dice[] , int DiceNumCnt[] , int Score[], int checked[], int count[] , int Checked[] , int end[])
{
    if (col1)
    {
        if (count[0] > 0) {
            if (cnt2)
            {
                count[0]--;
                EraseDice(Dice);
                DiceRoll(Dice, DiceNumCnt, Score, checked);
                ShowDice(Dice);
                ShowCount(count);
                ShowPreScore(Dice , DiceNumCnt , Score);
                Checked[0] = 0;
            }
            else
            {
                if (!checked[col2])
                {
                    gotoxy(35 + 4 * col2, 11);
                    cout << "ㅁ";
                    checked[col2] = 1;
                }
                else
                {
                    gotoxy(35 + 4 * col2, 11);
                    cout << "  ";
                    checked[col2] = 0;
                }
            }
        }
    }
    else
    {
        if (Dice[0] != -1)
        {
            if (cnt1 < 6)
            {
                if (Score[cnt1] == -1)
                {
                    if (Checked[0] == 0)
                    {
                        Score[cnt1] = CalcScore(cnt1, Dice, DiceNumCnt);
                        gotoxy(9, 2 * cnt1 + 1);
                        cout << "  ";
                        cout << Score[cnt1];
                        EraseDice(Dice);
                        count[0] = 3;
                        ShowCount(count);
                        for (int i = 0; i < 5; i++)
                        {
                            gotoxy(35 + 4 * i, 11);
                            cout << "  ";
                            checked[i] = 0;
                        }
                        Checked[0] = 1;
                        gotoxy(6, 27);
                        cout << "  ";
                        cout << TotalScore(Score);
                        gotoxy(6, 13);
                        cout << "  ";
                        cout << Subtotal(Score);
                        end[0]++;
                    }

                }
            }
            else
            {
                if (Score[cnt1] == -1)
                {
                    if (Checked[0] == 0)
                    {
                        Score[cnt1] = CalcScore(cnt1, Dice, DiceNumCnt);
                        gotoxy(9, 2 * cnt1 + 3);
                        cout << "  ";
                        cout << Score[cnt1];
                        EraseDice(Dice);
                        count[0] = 3;
                        ShowCount(count);
                        for (int i = 0; i < 5; i++)
                        {
                            gotoxy(35 + 4 * i, 11);
                            cout << "  ";
                            checked[i] = 0;
                        }
                        Checked[0] = 1;
                        gotoxy(6, 27);
                        cout << "  ";
                        cout << TotalScore(Score);
                        gotoxy(6, 13);
                        cout << "  ";
                        cout << Subtotal(Score);
                        end[0]++;
                    }
                }
            }
        }
    }
}
void StartGame()
{
    StartGameDraw();

    int Dice[5];
    for (int i = 0; i < 5; i++)
    {
        Dice[i] = -1;
    }
    int checked[5];
    for (int i = 0; i < 5; i++)
    {
        checked[i] = 0;
    }
    int DiceNumberCount[6];
    int Score[14];
    for (int i = 0; i < 13; i++)
    {
        Score[i] = -1;
    }
    Score[13] = 0;
    char c;

    int cnt1 = 6;
    int cnt2 = 1;
    int col1 = 1;
    int col2 = 4;

    int Checked[1];
    Checked[0] = 0;

    int count[1];
    count[0] = 3;
    int end[1];
    end[0] = 0;

    StartSetPoint(col1, col2, cnt1, cnt2);

    while (1)
    {
        if (_kbhit()) {
            c = _getch();
            if (c == SPACEBAR)
            {
                StartSelct(col1, col2, cnt1, cnt2, Dice, DiceNumberCount, Score, checked, count , Checked , end);
            }
            if (c == -32)
            {
                c = _getch();
                switch (c) {
                case UP:
                    StartErasePoint(col1,col2,cnt1, cnt2 );
                    if (col1 == 0)
                    {
                        if (cnt1 != 0) {
                            cnt1--;
                        }
                    }
                    else
                    {
                        if (cnt2 == 1) {
                            cnt2 =0;
                        }
                    }
                   StartSetPoint(col1,col2, cnt1, cnt2);
                    break;
                case DOWN:
                    StartErasePoint(col1, col2 ,cnt1, cnt2);
                    if (col1 == 0)
                    {
                        if (cnt1 != 11) {
                            cnt1++;
                        }
                    }
                    else
                    {
                        if (cnt2 == 0) {
                            cnt2 = 1;
                        }
                    }
                    StartSetPoint(col1, col2,cnt1, cnt2);
                    break;
                case RIGHT:
                    StartErasePoint(col1, col2, cnt1, cnt2);
                    if (col1 == 0)
                    {
                        col1 = 1;
                        if (cnt1 < 7)
                        {
                            col2 = 0;
                            cnt2 = 0;
                        }
                        else
                        {
                            cnt2 = 1;
                        }
                    }
                    else
                    {
                        if (col2 < 4)
                        {
                            col2++;
                        }
                    }
                    StartSetPoint(col1, col2, cnt1, cnt2);
                    break;
                case LEFT:
                    StartErasePoint(col1, col2, cnt1, cnt2);
                    if (col1)
                    {
                        if (cnt2)
                        {
                            cnt2 = 0;
                            col1 = 0;
                        }
                        else
                        {
                            if (col2 > 0)
                            {
                                col2--;
                            }
                            else
                            {
                                col1 = 0;
                            }
                        }
                    }
                    StartSetPoint(col1, col2, cnt1, cnt2);
                    break;
                }
            }
        }
        if (end[0] == 12)
        {
            break;
        }
    }
    endgame(Score);
}

void HelpNext()
{
    system("cls");
    MakeBasedLine();
    gotoxy(3, 4);
    cout << "Choice : 주사위 눈 5개의 총합.최대 30점. ";
    gotoxy(3, 7);
    cout << "4 of a Kind 동일한 주사위 눈이 4개 이상일 때, 주사위 눈 5개의 총합.최대 30점.";
    gotoxy(3, 10);
    cout << "Full House 주사위를 3개, 2개로 묶었을 때 각각의 묶음 안에서 주사위 눈이 서로 동일할 때, 주사위 눈 5개의 총합.";
    gotoxy(3, 13);
    cout << "Small Straight 이어지는 주사위 눈이 4개 이상일 때.고정 15점.";
    gotoxy(3, 16);
    cout << "Large Straight 이어지는 주사위 눈이 5개일 때.고정 30점.";
    gotoxy(3, 19);
    cout << "Yacht 동일한 주사위 눈이 5개일 때.고정 50점.";
    gotoxy(26, 26);
    cout << "메인 메뉴";
    gotoxy(31, 26);
    cout << "ㅇ";

    char c;
    while (1) {
        if (_kbhit()) {
            c = _getch();
            if (c == SPACEBAR)
            {
                return;
            }
        }
    }
}
void Help()
{
    MakeBasedLine();
    gotoxy(3, 4);
    cout << "Aces : 1이 나온 주사위 눈의 총합. 최대 5점";
    gotoxy(3, 7);
    cout << "Deuces : 2가 나온 주사위 눈의 총합. 최대 10점";
    gotoxy(3, 10);
    cout << "Threes : 3이 나온 주사위 눈의 총합. 최대 15점";
    gotoxy(3, 13);
    cout << "Fours : 4가 나온 주사위 눈의 총합. 최대 20점";
    gotoxy(3, 16);
    cout << "Fives : 5가 나온 주사위 눈의 총합. 최대 25점";
    gotoxy(3, 19);
    cout << "Sixes : 6이 나온 주사위 눈의 총합. 최대 30점";
    gotoxy(3, 22);
    cout << "보너스 : 상단 항목의 점수 합계가 63점 이상일 때, 35점을 추가로 얻는다.";
    gotoxy(28, 26);
    cout << "다음";
    gotoxy(31, 26);
    cout << "ㅇ";

    char c;

    while (1) 
    {
        if (_kbhit()) {
            c = _getch();
            if (c == SPACEBAR)
            {
                HelpNext();
                return;
            }
        }
    }
}

void MenuSetPoint(int cnt)
{
    switch (cnt)
    {
    case 0:
        gotoxy(33, 19);
        cout << "ㅇ";
        break;
    case 1:
        gotoxy(33, 21);
        cout << "ㅇ";
        break;
    case 2:
        gotoxy(33, 23);
        cout << "ㅇ";
        break;
    default:
        break;
    }
}
void MenuErasePoint(int cnt)
{
    switch (abs(cnt))
    {
    case 0:
        gotoxy(33, 19);
        cout << "  ";
        break;
    case 1:
        gotoxy(33, 21);
        cout << "  ";
        break;
    case 2:
        gotoxy(33, 23);
        cout << "  ";
        break;
    default:
        break;
    }
}
void DrawGameMenu()
{
    system("cls");
    MakeBasedLine();

    gotoxy(25, 8);
    cout << "Yacht   Dice !";
    gotoxy(26,19);
    cout << "게임 시작";
    gotoxy(27, 21);
    cout << "도움말";
    gotoxy(26, 23);
    cout << "게임 종료";
}
void Menu()
{
    DrawGameMenu();
    int IsSelected = False;
    int cnt = 0;
    MenuSetPoint(cnt);
    char c;

    while (1)
    {
        if (_kbhit()) {
            c = _getch();
            if (c == SPACEBAR)
            {
                system("cls");
                MenuSelect(cnt);
                break;
            }
            if (c == -32)
            {
                c = _getch();
                switch (c) {
                case UP:
                    MenuErasePoint(cnt);
                    if (cnt != 0)
                    {
                        cnt--;
                    }
                    MenuSetPoint(cnt);
                    break;
                case DOWN:
                    MenuErasePoint(cnt);
                    if (cnt != 2)
                    {
                        cnt++;
                    }
                    MenuSetPoint(cnt);
                    break;
                }
            }
        }
    }
}
void MenuSelect(int cnt)
{
    switch (cnt)
    {
    case 0:
        StartGame();
        break;

    case 1:
        Help();
        Menu();
        break;

    case 2:
        EndGame();
        break;
    }
}

int main()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    while (1)
    {
        Menu();
    }

    return 0;
}
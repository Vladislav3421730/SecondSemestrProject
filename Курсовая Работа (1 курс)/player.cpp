#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<fstream>
#include<string.h>
#include"passwords and check.h"
#include"menu.h"
#include"club.h"
#include<iomanip>
#include<string>
#include <vector>
#include <algorithm>
using namespace std;
struct player {
    string ID;
    string FIO;
    struct birthday
    {
        int day;
        int month;
        int year;
    }bd;
    int kol_of_match;
    int kol_of_goals;
    int kol_of_assists;
    int kol_of_minuts;
    int sum;
};

const string FILE_OF_PLAYERS = "file_of_playerss.txt";
vector<player> kol_of_player;
extern void Add_players() {
    int number;
    cout << "������� ������� �� ������ ������: ";
    cin >> number;
    number = check_on_letters(number);
    for (int i = 0; i < number; i++) {
        player* temp_player = new player();
        cout << "������� ���������� ������ " << i + 1 << endl;
        cout << "ID ������: ";
        getline(cin, temp_player->ID);
        cout << "��� ������: ";
        getline(cin, temp_player->FIO);
        temp_player->FIO = check_on_digit(temp_player->FIO);
        cout << "���� �������� (��.��.��): " << endl;
        cout << "    ����: ";
        cin >> temp_player->bd.day;
        temp_player->bd.day = check(1, 31, temp_player->bd.day);
        cout << "    �����: ";
        cin >> temp_player->bd.month;
        temp_player->bd.month = check(1, 12, temp_player->bd.month);
        cout << "    ���: ";
        cin >> temp_player->bd.year;
        temp_player->bd.year = check(1960, 2023, temp_player->bd.year);
        cout << "���������� ���������� ������: ";
        cin >> temp_player->kol_of_match;
        temp_player->kol_of_match = check_on_letters(temp_player->kol_of_match);
        cout << "���������� ������� ����: ";
        cin >> temp_player->kol_of_goals;
        temp_player->kol_of_goals = check_on_letters(temp_player->kol_of_goals);
        cout << "���������� ������� �������: ";
        cin >> temp_player->kol_of_assists;
        temp_player->kol_of_assists = check_on_letters(temp_player->kol_of_assists);
        cout << "���������� �������� �����: ";
        cin >> temp_player->kol_of_minuts;
        temp_player->kol_of_minuts = check_on_letters(temp_player->kol_of_minuts);
        temp_player->sum = temp_player->kol_of_goals + temp_player->kol_of_assists;
        cout << endl;
        kol_of_player.push_back(*temp_player);
        delete temp_player;
    }

}

extern void Write_in_file_player() {
    ofstream fadd(FILE_OF_PLAYERS, ios::out);
    for (int i = 0; i < kol_of_player.size(); i++) {
        fadd << kol_of_player[i].FIO << ","
            << kol_of_player[i].bd.day << ","
            << kol_of_player[i].bd.month << ","
            << kol_of_player[i].bd.year << ","
            << kol_of_player[i].ID << ","
            << kol_of_player[i].kol_of_assists << ","
            << kol_of_player[i].kol_of_goals << ","
            << kol_of_player[i].kol_of_match << ","
            << kol_of_player[i].kol_of_minuts << ","
            << kol_of_player[i].sum << endl;
    }
    fadd.close();
}
void copy_players_from_file()
{
    ifstream fin(FILE_OF_PLAYERS);
    if (!fin.is_open()) {
        cout << "������ �������� ����� " << FILE_OF_PLAYERS << endl;
        return;
    }
    string line;
    while (getline(fin, line)) {
        player* temp_player = new player();
        int pos = 0, prev_pos = 0;
        for (int i = 0; i < 9; i++)
        {
            pos = line.find(",", prev_pos);
            string value = line.substr(prev_pos, pos - prev_pos);
            switch (i)
            {
            case 0:
                temp_player->FIO = value;
                break;
            case 1:
                temp_player->bd.day = stoi(value);
                break;
            case 2:
                temp_player->bd.month = stoi(value);
                break;
            case 3:
                temp_player->bd.year = stoi(value);
                break;
            case 4:
                temp_player->ID = value;
                break;
            case 5:
                temp_player->kol_of_assists = stoi(value);
                break;
            case 6:
                temp_player->kol_of_goals = stoi(value);
                break;
            case 7:
                temp_player->kol_of_match = stoi(value);
                break;
            case 8:
                temp_player->kol_of_minuts = stoi(value);
                break;
            }
            prev_pos = pos + 1;
        }
        temp_player->sum = temp_player->kol_of_goals + temp_player->kol_of_assists;
        kol_of_player.push_back(*temp_player);
        delete temp_player;
    }
    fin.close();
}
extern void Output_players()
{
    if (!Size_of_File()) return;
    Output_first();
    for (int i = 0; i < kol_of_player.size(); i++)
        Output_need_players(i);
}
void extern Output_need_players(int i)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 2);
    cout << "|"; SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << setw(10) << kol_of_player[i].ID; SetConsoleTextAttribute(console, 2);
    cout << "  |"; SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); cout << setw(35) << kol_of_player[i].FIO; SetConsoleTextAttribute(console, 2);
    cout << "       |    "; SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << (kol_of_player[i].bd.day < 10 ? "0" : "") << (kol_of_player[i].bd.day < 10 ? setw(1) : setw(0)) << kol_of_player[i].bd.day << "." << (kol_of_player[i].bd.month < 10 ? "0" : "") << (kol_of_player[i].bd.month < 10 ? setw(1) : setw(0)) << kol_of_player[i].bd.month << "." << setw(4) << kol_of_player[i].bd.year;
    SetConsoleTextAttribute(console, 2); cout << " |"; SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << setw(8) << kol_of_player[i].kol_of_match; SetConsoleTextAttribute(console, 2); cout << "       |"; SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << setw(8) << kol_of_player[i].kol_of_goals; SetConsoleTextAttribute(console, 2); cout << "      |"; SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << setw(8) << kol_of_player[i].kol_of_assists; SetConsoleTextAttribute(console, 2); cout << "        |"; SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << setw(11) << kol_of_player[i].kol_of_minuts; SetConsoleTextAttribute(console, 2); cout << "            |"; SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << setw(5) << kol_of_player[i].sum; SetConsoleTextAttribute(console, 2); cout << "    |" << endl;
    cout << "|____________|__________________________________________|_______________|_______________|______________|________________|_______________________|_________|" << endl;
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
void extern Output_first()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 2);
    cout << "___________________________________________________________________________________________________________________________________________________________" << endl;
    cout << "|     "; SetConsoleTextAttribute(console, 5); cout << "ID";	SetConsoleTextAttribute(console, 2); cout << "     |"; SetConsoleTextAttribute(console, 5); cout << "                   ���                   ";
    SetConsoleTextAttribute(console, 2); cout << " |"; SetConsoleTextAttribute(console, 5); cout << " ���� ��������"; 	SetConsoleTextAttribute(console, 2); cout << " |"; SetConsoleTextAttribute(console, 5); cout << " ���-�� ������";
    SetConsoleTextAttribute(console, 2); cout << " |"; SetConsoleTextAttribute(console, 5); cout << " ���-�� ����� ";	SetConsoleTextAttribute(console, 2); cout << "|"; SetConsoleTextAttribute(console, 5);
    cout << " ���-�� �������";	SetConsoleTextAttribute(console, 2); cout << " |"; SetConsoleTextAttribute(console, 5); cout << " ���-�� �������� �����";	SetConsoleTextAttribute(console, 2);
    cout << " |"; SetConsoleTextAttribute(console, 5); cout << " ���+���";	SetConsoleTextAttribute(console, 2); cout << " | " << endl;
    cout << "|____________|__________________________________________|_______________|_______________|______________|________________|_______________________|_________|" << endl;
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
extern void delete_players()
{
    if (!Size_of_File()) return;
    cout << "������� ID ������ �������� �� ������ �������, ���� ������� ������� ���� ������� ������� 99" << endl;
    string ID;
    getline(cin, ID);
    if (ID == "99")
    {
        int choise;
        cout << "�� ����� ������ ������� ���� ������� (0/1)?" << endl;
        cin >> choise;
        choise = check(0, 1, choise);
        if (choise)
        {
            kol_of_player.clear();
            cout << "��� ������ �������." << endl;
        }
        else cout << "�� �������� ��� ������� ������� ���� �������" << endl;
    }
    else
    {
        bool n = false;
        register int i;
        for (i = 0; i < kol_of_player.size(); i++)
            if (kol_of_player[i].ID == ID)
            {
                n = true;
                break;
            }
        if (!n) cout << "����� � ID " << ID << " �� ��� ������" << endl;
        else
        {
            if (n) cout << "�� ����� ������ ������� ������" << endl;
            Output_first();
            Output_need_players(i);
            int choise;
            cout << "�� ����� ������ ������� ����� ������ (0/1)?" << endl;
            cin >> choise;
            choise = check(0, 1, choise);
            if (choise)
            {
                kol_of_player.erase(kol_of_player.begin() + i);
                cout << "����� � ID " << ID << " ��� �����" << endl;
            }
            else cout << "�� �������� ��� �������" << endl;
        }
    }
}
extern void edit_players()
{
    if (!Size_of_File()) return;
    string id;
    cout << "������� ID ������: ";
    getline(cin, id);
    int player_index = -1;
    for (int i = 0; i < kol_of_player.size(); i++) {
        if (kol_of_player[i].ID == id) {
            player_index = i;
            break;
        }
    }
    if (player_index == -1) {
        cout << "����� � ����� ID �� ������." << endl;
        return;
    }
    cout << "��������, ����� �������������� ������ �� ������ ��������:" << endl;
    cout << "1. ���" << endl;
    cout << "2. ���� ��������" << endl;
    cout << "3. ���������� ����������� ������" << endl;
    cout << "4. ���������� ������� ����" << endl;
    cout << "5. ���������� ������� �������" << endl;
    cout << "6. ���������� �������� �����" << endl;
    cout << "7. � ����" << endl;
    int choice;
    cin >> choice;
    choice = check(1, 7, choice);
    switch (choice) {
    case 1: {
        string new_fio;
        cout << "������� ����� ���: ";
        getline(cin, new_fio);
        new_fio = check_on_digit(new_fio);
        int confirm;
        cout << "�� ����� ������ �������� ������ �������������� (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            kol_of_player[player_index].FIO = new_fio;
            cout << "��� ��������." << endl;
        }
        else {
            cout << "��� �� ��������." << endl;
        }

        break;
    }

    case 2: {
        int new_day, new_month, new_year;
        cout << "������� ����� ���� �������� (��.��.��):" << endl;
        cout << "    ����: ";
        cin >> new_day;
        new_day = check(1, 31, new_day);
        cout << "    �����: ";
        cin >> new_month;
        new_month = check(1, 12, new_month);
        cout << "    ���: ";
        cin >> new_year;
        new_year = check(1900, 2023, new_year);
        int confirm;
        cout << "�� ����� ������ �������� ������ �������������� (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            kol_of_player[player_index].bd.day = new_day;
            kol_of_player[player_index].bd.month = new_month;
            kol_of_player[player_index].bd.year = new_year;
            cout << "���� �������� ��������." << endl;
        }
        else {
            cout << "���� �������� �� ��������." << endl;
        }

        break;
    }
    case 3: {
        int new_kol_of_match;
        cout << "������� ����� ���������� ����������� ������: ";
        cin >> new_kol_of_match;
        new_kol_of_match = check_on_letters(new_kol_of_match);
        int confirm;
        cout << "�� ����� ������ �������� ������ �������������� (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1)
        {
            kol_of_player[player_index].kol_of_match = new_kol_of_match;
            cout << "���������� ������ ��������" << endl;
        }
        else cout << "���������� ������ �� ��������" << endl;
        break;
    }
    case 4: {
        int new_kol_of_goals;
        cout << "������� ����� ���������� �����: ";
        cin >> new_kol_of_goals;
        new_kol_of_goals = check_on_letters(new_kol_of_goals);
        int confirm;
        cout << "�� ����� ������ �������� ������ �������������� (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1)
        {
            kol_of_player[player_index].kol_of_goals = new_kol_of_goals;
            cout << "���������� ����� ��������" << endl;
        }
        else cout << "���������� ����� �� ��������" << endl;
        break;
    }
    case 5: {
        int new_kol_of_assist;
        cout << "������� ����� ���������� �����: ";
        cin >> new_kol_of_assist;
        new_kol_of_assist = check(0, 1, new_kol_of_assist);
        int confirm;
        cout << "�� ����� ������ �������� ������ �������������� (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1)
        {
            kol_of_player[player_index].kol_of_assists = new_kol_of_assist;
            kol_of_player[player_index].sum = kol_of_player[player_index].kol_of_goals + kol_of_player[player_index].kol_of_assists;
            cout << "���������� ����� ��������" << endl;
        }
        else cout << "���������� ����� �� ��������" << endl;
        break;
    }
    case 6:
    {
        int new_kol_of_min;
        cout << "������� ����� ���������� �������� �����: ";
        cin >> new_kol_of_min;
        new_kol_of_min = check(0, 1, new_kol_of_min);
        int confirm;
        cout << "�� ����� ������ �������� ������ �������������� (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1)
        {
            kol_of_player[player_index].kol_of_minuts = new_kol_of_min;
            kol_of_player[player_index].sum = kol_of_player[player_index].kol_of_goals + kol_of_player[player_index].kol_of_assists;
            cout << "���������� �������� ����� ��������" << endl;
        }
        else cout << "���������� �������� �� ��������" << endl;
        break;
    }
    }
}
extern void poisk_players(int n)
{
    switch (n)
    {
    case 1:
    {
        register int count1 = 1;
        string poisk_ID;
        cout << "������� ID ������, �������� �� ������ �����" << endl;
        getline(cin, poisk_ID);
        poisk_ID = check_on_size(poisk_ID, 3);
        for (register int i = 0; i < kol_of_player.size(); i++)
        {
            if (kol_of_player[i].ID.find(poisk_ID) != string::npos)
            {
                count1--;
                if (!count1)
                {
                    cout << "���������� �� ID: " << poisk_ID << endl;
                    Output_first();
                }
                Output_need_players(i);
            }
        }
        if (count1 == 1) cout << "����� � ID " << poisk_ID << " �� ��� ������." << endl;
    }break;
    case 2:
    {
        register int count2 = 1;
        string poisk_FIO;
        cout << "������� ��� ������, �������� �� ������ �����" << endl;
        getline(cin, poisk_FIO);
        poisk_FIO = check_on_size(poisk_FIO, 5);
        for (register int i = 0; i < kol_of_player.size(); i++)
        {
            if (kol_of_player[i].FIO.find(poisk_FIO) != string::npos)
            {
                count2--;
                if (!count2)
                {
                    cout << "���������� �� ���: " << poisk_FIO << endl;
                    Output_first();
                }
                Output_need_players(i);
            }
        }
        if (count2 == 1) cout << "����� � ��� " << poisk_FIO << " �� ��� ������." << endl;
    }break;
    case 3:
    {
        register int count3 = 1;
        int poisk_bithday;
        cout << "������� ��� �������� ������, �������� �� ������ �����" << endl;
        cin >> poisk_bithday;
        poisk_bithday = check_on_letters(poisk_bithday);
        for (register int i = 0; i < kol_of_player.size(); i++)
        {
            if (poisk_bithday == kol_of_player[i].bd.year)
            {
                count3--;
                if (!count3)
                {
                    cout << "���������� �� ���� ��������: " << poisk_bithday << endl;
                    Output_first();
                }
                Output_need_players(i);
            }
        }
        if (count3 == 1) cout << "����� � ����� ��������  " << poisk_bithday << " �� ��� ������." << endl;
    }break;
    case 4:
    {
        register int count4 = 1;
        int poisk_kol_of_match;
        cout << "������� ���������� ������ ������, �������� �� ������ �����" << endl;
        cin >> poisk_kol_of_match;
        poisk_kol_of_match = check_on_letters(poisk_kol_of_match);
        for (register int i = 0; i < kol_of_player.size(); i++)
        {
            if (poisk_kol_of_match == kol_of_player[i].kol_of_match)
            {
                count4--;
                if (!count4)
                {
                    cout << "���������� �� ���������� ������: " << poisk_kol_of_match << endl;
                    Output_first();
                }
                Output_need_players(i);
            }
        }
        if (count4 == 1) cout << "����� � ����������� ������  " << poisk_kol_of_match << " �� ��� ������." << endl;
    }break;
    case 5:
    {
        register int count5 = 1;
        int poisk_kol_of_goals;
        cout << "������� ���������� ������� ����  ������, �������� �� ������ �����" << endl;
        cin >> poisk_kol_of_goals;
        poisk_kol_of_goals = check_on_letters(poisk_kol_of_goals);
        for (register int i = 0; i < kol_of_player.size(); i++)
        {
            if (poisk_kol_of_goals == kol_of_player[i].kol_of_goals)
            {
                count5--;
                if (!count5)
                {
                    cout << "���������� �� ���������� ������� ����: " << poisk_kol_of_goals << endl;
                    Output_first();
                }
                Output_need_players(i);
            }
        }
        if (count5 == 1) cout << "����� � ����������� ������� ����  " << poisk_kol_of_goals << " �� ��� ������." << endl;
    }break;
    case 6:
    {
        register int count6 = 1;
        int poisk_kol_of_assists;
        cout << "������� ���������� ����� ������, �������� �� ������ �����" << endl;
        cin >> poisk_kol_of_assists;
        poisk_kol_of_assists = check_on_letters(poisk_kol_of_assists);
        for (register int i = 0; i < kol_of_player.size(); i++)
        {
            if (poisk_kol_of_assists == kol_of_player[i].kol_of_assists)
            {
                count6--;
                if (!count6)
                {
                    cout << "���������� �� ���������� ���� ������: " << poisk_kol_of_assists << endl;
                    Output_first();
                }
                Output_need_players(i);
            }
        }
        if (count6 == 1) cout << "����� � ����������� �����   " << poisk_kol_of_assists << " �� ��� ������." << endl;
    }break;
    case 7:
    {
        register int count7 = 1;
        int poisk_kol_of_minuts;
        cout << "������� ���������� �������� ����� ������, �������� �� ������ �����" << endl;
        cin >> poisk_kol_of_minuts;
        poisk_kol_of_minuts = check_on_letters(poisk_kol_of_minuts);
        for (register int i = 0; i < kol_of_player.size(); i++)
        {
            if (poisk_kol_of_minuts == kol_of_player[i].kol_of_minuts)
            {
                count7--;
                if (!count7)
                {
                    cout << "���������� �� ���������� �������� ����� ������: " << poisk_kol_of_minuts << endl;
                    Output_first();
                }
                Output_need_players(i);
            }
        }
        if (count7 == 1) cout << "����� � ����������� �������� �����  " << poisk_kol_of_minuts << " �� ��� ������." << endl;
    }break;
    }
}
bool compare_by_FIO(const player& a, const player& b) {
    return a.FIO < b.FIO;
}

bool compare_by_kol_of_games(const player& a, const player& b) {
    return a.kol_of_match > b.kol_of_match;
}

bool compare_by_kol_of_goals(const player& a, const player& b) {
    return a.kol_of_goals > b.kol_of_goals;
}

bool compare_by_bd_year(const player& a, const player& b) {
    return a.bd.year < b.bd.year;
}
bool compare_by_kol_of_goals_assists(const player& a, const player& b) {
    return a.sum > b.sum;
}
extern void sort_players()
{
    if (!Size_of_File()) return;
    int choice;
    cout << "�������� ���� ��� ����������:\n";
    cout << "1. ���\n";
    cout << "2. ���������� ������\n";
    cout << "3. ���������� �����\n";
    cout << "4. ��� ��������\n";
    cout << "5. � ����" << endl;
    cin >> choice;
    choice = check(1, 5, choice);
    switch (choice) {
    case 1:
        sort(kol_of_player.begin(), kol_of_player.end(), compare_by_FIO);
        cout << "��� ������ ���� ������������� �� ���" << endl;
        break;
    case 2:
        sort(kol_of_player.begin(), kol_of_player.end(), compare_by_kol_of_games);
        cout << "��� ������ ���� ������������� �� ���������� ���" << endl;
        break;
    case 3:
        sort(kol_of_player.begin(), kol_of_player.end(), compare_by_kol_of_goals);
        cout << "��� ������ ���� ������������� �� ���������� �����" << endl;
        break;
    case 4:
        sort(kol_of_player.begin(), kol_of_player.end(), compare_by_bd_year);
        cout << "��� ������ ���� ������������� �� ���� ��������" << endl;
        break;
    }
    if (choice != 5) Output_players();
}
extern bool Size_of_File()
{
    if (!kol_of_player.size()) { cout << "�� ������ ������ ��� ������������������ �������" << endl; return false; }
}
extern void Output_top_six()
{
    if (!Size_of_File()) return;
    sort(kol_of_player.begin(), kol_of_player.end(), compare_by_kol_of_goals_assists);
    if (kol_of_player.size() < 6)
    {
        cout << "�� ������ ������ ������� ��������: " << kol_of_player.size() << endl;
        Output_players();
    }
    else
    {
        Output_first();
        for (register int i = 0; i < 6; i++)
            Output_need_players(i);
    }
    kol_of_player.clear();
    copy_players_from_file();
}

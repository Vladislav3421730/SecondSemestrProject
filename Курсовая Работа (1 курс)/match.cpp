#include<iostream>
#include<Windows.h>
#include<fstream>
#include<string.h>
#include"passwords and check.h"
#include"menu.h"
#include"club.h"
#include<iomanip>
#include<string>
#include <vector>
#include <algorithm>
#include<time.h>
#include <conio.h>
#define get_color  SetConsoleTextAttribute(console, 6);
#define other_color  SetConsoleTextAttribute(console, 2);
#define no_color  SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
using namespace std;
struct match
{
    string teams;
    string stadium;
    int tickets;
    struct data_match
    {
        int day;
        int month;
    } data;
    struct time_match
    {
        int hour;
        int minuts;

    } time;
};
const string FILE_OF_MATCHES = "file_of_match.txt";
vector<match> all_matches;
extern void Add_match()
{
    int number;
    cout << "������� ������ �� ������ ������: ";
    cin >> number;
    number = check_on_letters(number);
    for (int i = 0; i < number; i++) {
        match* temp_match = new match();
        cout << "������� ���������� � ����� " << i + 1 << endl;
        cout << "�������: ";
        getline(cin, temp_match->teams);
        temp_match->teams = check_on_digit(temp_match->teams);
        cout << "�������: ";
        getline(cin, temp_match->stadium);
        temp_match->stadium = check_on_digit(temp_match->stadium);
        cout << "���������� ��������� ������� (���������, ���� ���� ������): ";
        cin >> temp_match->tickets;
        temp_match->tickets = check_on_letters(temp_match->tickets);
        cout << "���� ���������� �����: " << endl;
        cout << " ����: ";
        cin >> temp_match->data.day;
        temp_match->data.day = check(1, 31, temp_match->data.day);
        cout << " �����: ";
        cin >> temp_match->data.month;
        temp_match->data.month = check(1, 12, temp_match->data.month);
        cout << "����� ������ �����: " << endl;
        cout << " ����: ";
        cin >> temp_match->time.hour;
        temp_match->time.hour = check(0, 24, temp_match->time.hour);
        cout << " ������: ";
        cin >> temp_match->time.minuts;
        temp_match->time.minuts = check(0, 60, temp_match->time.minuts);
        all_matches.push_back(*temp_match);
        delete temp_match;
    }
}

extern void Write_in_file_match() {
    ofstream fadd(FILE_OF_MATCHES, ios::out);
    for (int i = 0; i < all_matches.size(); i++) {
        fadd << all_matches[i].teams << ","
            << all_matches[i].stadium << ","
            << all_matches[i].tickets << ","
            << all_matches[i].data.day << ","
            << all_matches[i].data.month << ","
            << all_matches[i].time.hour << ","
            << all_matches[i].time.minuts << endl;
    }
    fadd.close();
}

extern void copy_match_from_file()
{
    ifstream fin(FILE_OF_MATCHES);
    if (!fin.is_open())
    {
        cout << "������ �������� ����� " << FILE_OF_MATCHES << endl;
        return;
    }
    string line;
    while (getline(fin, line))
    {
        match temp_match;
        int pos = 0, prev_pos = 0;
        for (int i = 0; i < 7; i++)
        {
            pos = line.find(",", prev_pos);
            string value = line.substr(prev_pos, pos - prev_pos);
            switch (i)
            {
            case 0:
                temp_match.teams = value;
                break;
            case 1:
                temp_match.stadium = value;
                break;
            case 2:
                temp_match.tickets = stoi(value);
                break;
            case 3:
                temp_match.data.day = stoi(value);
                break;
            case 4:
                temp_match.data.month = stoi(value);
                break;
            case 5:
                temp_match.time.hour = stoi(value);
                break;
            case 6:
                temp_match.time.minuts = stoi(value);
                break;
            }
            prev_pos = pos + 1;
        }
        all_matches.push_back(temp_match);
    }
}
extern void delete_match()
{
    if (!Size_of_File_match()) return;
    cout << "������� ������� �����, �������� �� ������ �������, ���� ������ ������� ��� ����� 99" << endl;
    string teams;
    getline(cin, teams);
    if (teams == "99")
    {
        int choise;
        cout << "�� ����� ������ ������� �� ���������� ����� (0/1)?" << endl;
        cin >> choise;
        choise = check(0, 1, choise);
        if (choise)
        {
            all_matches.clear();
            cout << "��� ��������� �������." << endl;
        }
        else cout << "�� �������� ��� ������� ������� ���������� ���� ������" << endl;
    }
    else
    {
        bool n = false;
        register int i;
        for (i = 0; i < all_matches.size(); i++)
            if (all_matches[i].teams == teams)
            {
                n = true;
                break;
            }
        if (!n) cout << "�������" << teams << " �� ��� ������" << endl;
        else
        {
            if (n) cout << "�� ����� ������ ������� ������ ����" << endl;
            Output_first_staff();
            Output_need_staff(i);
            int choise;
            cout << "�� ����� ������ ������� ���� ���� (0/1)?" << endl;
            cin >> choise;
            choise = check(0, 1, choise);
            if (choise)
            {
                all_matches.erase(all_matches.begin() + i);
                cout << "���� � ���������" << teams << " ��� �����" << endl;
            }
            else cout << "�� �������� ��� �������" << endl;
        }
    }
}
void edit_match()
{
    if (!Size_of_File_match()) return;
    string teams;
    cout << "������� �������� ������: ";
    getline(cin, teams);
    int match_index = -1;
    for (int i = 0; i < all_matches.size(); i++) {
        if (all_matches[i].teams == teams) {
            match_index = i;
            break;
        }
    }
    if (match_index == -1) {
        cout << "���� � ����� ��������� ������ �� ������." << endl;
        return;
    }
    cout << "��������, ����� �������������� ����� �� ������ ��������:" << endl;
    cout << "1. �������" << endl;
    cout << "2. ������" << endl;
    cout << "3. ����" << endl;
    cout << "4. �����" << endl;
    cout << "5. �������" << endl;
    cout << "6. � ����" << endl;
    int choice;
    cin >> choice;
    choice = check(1, 6, choice);
    switch (choice) {
    case 1: {
        string new_teams;
        cout << "������� ����� �������: ";
        getline(cin, new_teams);
        new_teams = check_on_digit(new_teams);
        int confirm;
        cout << "�� ����� ������ �������� ������ �������������� (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            all_matches[match_index].teams = new_teams;
            cout << "�������� ������ ��������." << endl;
        }
        else  cout << "�������� ������ �� ��������." << endl;
        break;
    }
    case 2:
    {
        int new_tickets;
        cout << "������� ����� ���������� �������: ";
        cin >> new_tickets;
        new_tickets = check_on_letters(new_tickets);
        int confirm;
        cout << "�� ����� ������ �������� ������ �������������� (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            all_matches[match_index].tickets = new_tickets;
            cout << "���������� ������� ��������." << endl;
        }
        else {
            cout << "���������� ������� �� ��������." << endl;
        }

        break;
    }

    case 3: {
        int new_day, new_month;
        cout << "������� ����� ���� (��.��): ";
        cout << " ���� :";
        cin >> new_day;
        new_day = check(1, 31, new_day);
        cout << " ����� :";
        cin >> new_month;
        new_month = check(1, 12, new_month);
        int confirm;
        cout << "�� ����� ������ �������� ������ �������������� (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            all_matches[match_index].data.day = new_day;
            all_matches[match_index].data.month = new_month;
            cout << "���� ��������." << endl;
        }
        else cout << "���� �� ��������." << endl;
        break;
    }

    case 4: {
        int new_hour, new_minutes;
        cout << "������� ����� ����� (��:��): ";
        cout << " ��� :";
        cin >> new_hour;
        new_hour = check(0, 24, new_hour);
        cout << " ������ :";
        cin >> new_minutes;
        new_minutes = check(0, 60, new_minutes);
        int confirm;
        cout << "�� ����� ������ �������� ������ �������������� (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            all_matches[match_index].time.hour = new_hour;
            all_matches[match_index].time.minuts = new_minutes;
            cout << "����� ��������." << endl;
        }
        else cout << "����� �� ��������." << endl;
        break;
    }
    case 5:
    {
        string new_stadium;
        cout << "������� ����� ������� ����������: ";
        getline(cin, new_stadium);
        new_stadium = check_on_digit(new_stadium);
        int confirm;
        cout << "�� ����� ������ �������� ������ �������������� (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            all_matches[match_index].stadium = new_stadium;
            cout << "������� ���������� ��������." << endl;
        }
        else  cout << "������ ����������  �� ������." << endl;
        break;
    }
    }
}
extern void poisk_match(int n)
{
    switch (n)
    {
    case 1:
    {
        int count1 = 0;
        string poisk_teams;
        cout << "������� �������: ";
        getline(cin, poisk_teams);
        poisk_teams = check_on_size(poisk_teams, 4);
        for (int i = 0; i < all_matches.size(); i++)
        {
            if (all_matches[i].teams.find(poisk_teams) != string::npos)
            {
                count1++;
                if (count1 == 1)
                {
                    cout << "���������� �� ��������: " << poisk_teams << endl;
                    Output_first_match();
                }
                Output_need_match(i);
            }
        }
        if (count1 == 0)
            cout << "����� � �������� " << poisk_teams << " �� �������." << endl;
    }
    break;
    case 2:
    {
        int count2 = 0;
        string poisk_stadium;
        cout << "������� �������� ��������: ";
        getline(cin, poisk_stadium);
        poisk_stadium = check_on_size(poisk_stadium, 3);
        for (int i = 0; i < all_matches.size(); i++)
        {
            if (all_matches[i].stadium.find(poisk_stadium) != string::npos)
            {
                count2++;
                if (count2 == 1)
                {
                    cout << "���������� �� ��������: " << poisk_stadium << endl;
                    Output_first_match();
                }
                Output_need_match(i);
            }
        }
        if (count2 == 0)
            cout << "����� �� �������� " << poisk_stadium << " �� �������." << endl;
    }
    break;
    case 3:
    {
        int count3 = 0;
        int poisk_day, poisk_month;
        cout << "������� ���� �����: ";
        cin >> poisk_day;
        poisk_day = check_on_letters(poisk_day);
        cout << "������� ����� �����: ";
        cin >> poisk_month;
        poisk_month = check_on_letters(poisk_month);
        for (int i = 0; i < all_matches.size(); i++)
        {
            if (poisk_day == all_matches[i].data.day && poisk_month == all_matches[i].data.month)
            {
                count3++;
                if (count3 == 1)
                {
                    cout << "���������� �� ����: " << poisk_day << "." << poisk_month << endl;
                    Output_first_match();
                }
                Output_need_match(i);
            }
        }
        if (count3 == 0)
            cout << "����� �� ���� " << poisk_day << "." << poisk_month << " �� �������." << endl;
    }
    break;
    }
}
bool compare_by_teams(const match& a, const match& b) {
    return a.teams < b.teams;
}

bool compare_by_date(const match& a, const match& b) {
    if (a.data.month != b.data.month) {
        return a.data.month < b.data.month;
    }
    return a.data.day < b.data.day;
}

bool compare_by_time(const match& a, const match& b) {
    if (a.time.hour != b.time.hour) {
        return a.time.hour < b.time.hour;
    }
    return a.time.minuts < b.time.minuts;
}

bool compare_by_stadium(const match& a, const match& b) {
    return a.stadium < b.stadium;
}

void sort_match()
{
    if (!Size_of_File_match()) return;
    int choice;
    cout << "�������� ���� ��� ����������:\n";
    cout << "1. �������\n";
    cout << "2. ���� (����, �����)\n";
    cout << "3. ����� (����, ������)\n";
    cout << "4. ������� ����������\n";
    cout << "5. � ����" << endl;
    cin >> choice;
    choice = check(0, 5, choice);
    switch (choice) {
    case 1:
        sort(all_matches.begin(), all_matches.end(), compare_by_teams);
        cout << "��� ����� ���� ������������� �� ��������" << endl;
        break;
    case 2:
        sort(all_matches.begin(), all_matches.end(), compare_by_date);
        cout << "��� ����� ���� ������������� �� ����" << endl;
        break;
    case 3:
        sort(all_matches.begin(), all_matches.end(), compare_by_time);
        cout << "��� ����� ���� ������������� �� �������" << endl;
        break;
    case 4:
        sort(all_matches.begin(), all_matches.end(), compare_by_stadium);
        cout << "��� ����� ���� ������������� �� �������� ����������" << endl;
        break;
    }
    if (choice != 5) Output_match();
}
extern void Output_first_match()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    get_color
        cout << "__________________________________________________________________________________________________________________________________" << endl;
    cout << "|"; other_color cout << "            �������   "; get_color cout << "        |"; other_color
        cout << "          ������� ����������          "; get_color cout << "|"; other_color
        cout << "      ����     "; get_color cout << "|"; other_color
        cout << "   �����  "; get_color cout << "|         "; other_color
        cout << " ��������� ������     "; get_color cout << "|" << endl;
    cout << "|______________________________|______________________________________|_______________|__________|_______________________________|" << endl;
    no_color
}
bool Gettime(int i)
{
    int day, month, hour, minuts;
    SYSTEMTIME tm;
    GetLocalTime(&tm);
    struct tm localtime;
    time_t now = time(NULL);
    localtime_s(&localtime, &now);
    day = localtime.tm_mday;
    month = 1 + localtime.tm_mon;
    hour = localtime.tm_hour;
    minuts = localtime.tm_min;
    int count = 0;
    count++;
    if (month > all_matches[i].data.month) { count++; return false; }
    else if (month == all_matches[i].data.month) if (day > all_matches[i].data.day) { count++; return false; }
    else if (month == all_matches[i].data.month && (day == all_matches[i].data.day)) if (hour > all_matches[i].time.hour) { count++; return false; }
    else if (month == all_matches[i].data.month && (day == all_matches[i].data.day) && hour == all_matches[i].time.hour) if (minuts > all_matches[i].time.minuts) { count++; return false; }
    if (!count) return true;
}
extern void Output_need_match(int i)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    get_color
        cout << "|     "; no_color cout << setw(20) << all_matches[i].teams;   get_color cout << "     |     "; no_color
        cout << setw(23) << all_matches[i].stadium;   get_color cout << "          |     ";
    no_color cout << (all_matches[i].data.day < 10 ? setw(1) : setw(0)) << (all_matches[i].data.day < 10 ? "0" : "") << all_matches[i].data.day << "."
        << (all_matches[i].data.month < 10 ? setw(1) : setw(0)) << (all_matches[i].data.month < 10 ? "0" : "") << all_matches[i].data.month;
    get_color
        cout << "     |   ";  no_color cout << (all_matches[i].time.hour < 10 ? setw(1) : setw(0)) << (all_matches[i].time.hour < 10 ? "0" : "")
        << all_matches[i].time.hour << ":" << (all_matches[i].time.minuts < 10 ? setw(1) : setw(0))
        << (all_matches[i].time.minuts < 10 ? "0" : "") << all_matches[i].time.minuts;
    get_color cout << "  |        "; no_color cout << setw(10) << all_matches[i].tickets;
    get_color cout << "             |" << endl;
    cout << "|______________________________|______________________________________|_______________|__________|_______________________________|" << endl;
    no_color
}
extern void Output_match()
{
    if (!Size_of_File_match()) return;
    Output_first_match();
    for (int i = 0; i < all_matches.size(); i++)
        Output_need_match(i);
}
extern bool Size_of_File_match()
{
    if (!all_matches.size()) { cout << "��� ���������� � ������" << endl; return false; }
}
extern void Get_past_match()
{
    if (!Size_of_File_match()) return;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    get_color
        cout << "__________________________________________________________________________________________________________________________________" << endl;
    cout << "|"; other_color cout << "            �������   "; get_color cout << "        |"; other_color
        cout << "          ������� ����������          "; get_color cout << "|"; other_color
        cout << "      ����     "; get_color cout << "|"; other_color
        cout << "   �����  "; get_color cout << "|         "; other_color
        cout << " ��������� ������     "; get_color cout << "|" << endl;
    cout << "|______________________________|______________________________________|_______________|__________|_______________________________|" << endl;
    no_color
        for (int i = 0; i < all_matches.size(); i++)
            if (!Gettime(i))   Output_need_match(i);

}
extern void Get_future_match()
{
    if (!Size_of_File_match()) return;
    Output_first_match();
    for (int i = 0; i < all_matches.size(); i++)
        if (Gettime(i))   Output_need_match(i);
}


extern  void buy_tickets()
{
    if (!Size_of_File_match()) return;
    string teams;
    cout << "����� ������ ������ �� ���� ������� ������� (������: ������ - �������)" << endl;
    cin.ignore();
    getline(cin, teams);
    int i, tickets, show = 0;
    for (i = 0; i < all_matches.size(); i++)
        if (all_matches[i].teams.find(teams) != string::npos)
        {
            show++;
            break;
        }
    if (!show) { cout << "����� ������ ���" << endl; return; }
    if (!Gettime(i)) { cout << "���� " << all_matches[i].teams << " ��� ������, �� ���� ������ ������������� �����" << endl; return; }
    cout << "������� ������� �� ������ ������������� �� ���� " << all_matches[i].teams << " ?" << endl;
    cin >> tickets;
    tickets = check(1, 100, tickets);
    if (all_matches[i].tickets - tickets <= 0) { cout << "� ��������� �� ������ ���� ��� �������" << endl; return; }
    cout << "�� ����� ������ ������������� ������ (1/0) ?" << endl;
    int choise;
    cin >> choise;
    choise = check(0, 1, choise);
    if (choise == 1)
    {
        all_matches[i].tickets = all_matches[i].tickets - tickets;
        cout << (tickets == 1 ? "����� ��� ������� ������������" : "������ ���� ������� �������������") << " �� ���� " << all_matches[i].teams << endl;
        Write_in_file_match();
    }
    else cout << "�� �������� ��� �������" << endl;
}
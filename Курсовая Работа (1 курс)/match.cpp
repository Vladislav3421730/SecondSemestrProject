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
    cout << "Сколько матчей вы хотите ввести: ";
    cin >> number;
    number = check_on_letters(number);
    for (int i = 0; i < number; i++) {
        match* temp_match = new match();
        cout << "Введите информацию о матче " << i + 1 << endl;
        cout << "Команды: ";
        getline(cin, temp_match->teams);
        temp_match->teams = check_on_digit(temp_match->teams);
        cout << "Стадион: ";
        getline(cin, temp_match->stadium);
        temp_match->stadium = check_on_digit(temp_match->stadium);
        cout << "Количество доступных билетов (проданных, если матч прошёл): ";
        cin >> temp_match->tickets;
        temp_match->tickets = check_on_letters(temp_match->tickets);
        cout << "Дата проведения матча: " << endl;
        cout << " День: ";
        cin >> temp_match->data.day;
        temp_match->data.day = check(1, 31, temp_match->data.day);
        cout << " Месяц: ";
        cin >> temp_match->data.month;
        temp_match->data.month = check(1, 12, temp_match->data.month);
        cout << "Время начала матча: " << endl;
        cout << " Часы: ";
        cin >> temp_match->time.hour;
        temp_match->time.hour = check(0, 24, temp_match->time.hour);
        cout << " Минуты: ";
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
        cout << "Ошибка открытия файла " << FILE_OF_MATCHES << endl;
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
    cout << "Введите команды матча, которого вы хотите удалить, Если хотите удалить все матчи 99" << endl;
    string teams;
    getline(cin, teams);
    if (teams == "99")
    {
        int choise;
        cout << "Вы точно хотите удалить всё расписание матча (0/1)?" << endl;
        cin >> choise;
        choise = check(0, 1, choise);
        if (choise)
        {
            all_matches.clear();
            cout << "Все работники удалены." << endl;
        }
        else cout << "Вы отменили своё решение удалить расписание всех матчей" << endl;
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
        if (!n) cout << "Команды" << teams << " не был найден" << endl;
        else
        {
            if (n) cout << "Вы точно хотите удалить данный матч" << endl;
            Output_first_staff();
            Output_need_staff(i);
            int choise;
            cout << "Вы точно хотите удалить этот матч (0/1)?" << endl;
            cin >> choise;
            choise = check(0, 1, choise);
            if (choise)
            {
                all_matches.erase(all_matches.begin() + i);
                cout << "Матч с командами" << teams << " был удалён" << endl;
            }
            else cout << "Вы отменили своё решение" << endl;
        }
    }
}
void edit_match()
{
    if (!Size_of_File_match()) return;
    string teams;
    cout << "Введите название команд: ";
    getline(cin, teams);
    int match_index = -1;
    for (int i = 0; i < all_matches.size(); i++) {
        if (all_matches[i].teams == teams) {
            match_index = i;
            break;
        }
    }
    if (match_index == -1) {
        cout << "Матч с таким названием команд не найден." << endl;
        return;
    }
    cout << "Выберите, какую характеристику матча вы хотите изменить:" << endl;
    cout << "1. Команды" << endl;
    cout << "2. Билеты" << endl;
    cout << "3. Дата" << endl;
    cout << "4. Время" << endl;
    cout << "5. Стадион" << endl;
    cout << "6. В меню" << endl;
    int choice;
    cin >> choice;
    choice = check(1, 6, choice);
    switch (choice) {
    case 1: {
        string new_teams;
        cout << "Введите новые команды: ";
        getline(cin, new_teams);
        new_teams = check_on_digit(new_teams);
        int confirm;
        cout << "Вы точно хотите изменить данную характеристику (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            all_matches[match_index].teams = new_teams;
            cout << "Название команд изменено." << endl;
        }
        else  cout << "Название команд не изменено." << endl;
        break;
    }
    case 2:
    {
        int new_tickets;
        cout << "Введите новое количество билетов: ";
        cin >> new_tickets;
        new_tickets = check_on_letters(new_tickets);
        int confirm;
        cout << "Вы точно хотите изменить данную характеристику (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            all_matches[match_index].tickets = new_tickets;
            cout << "Количество билетов изменено." << endl;
        }
        else {
            cout << "Количество билетов не изменено." << endl;
        }

        break;
    }

    case 3: {
        int new_day, new_month;
        cout << "Введите новую дату (ДД.ММ): ";
        cout << " День :";
        cin >> new_day;
        new_day = check(1, 31, new_day);
        cout << " Месяц :";
        cin >> new_month;
        new_month = check(1, 12, new_month);
        int confirm;
        cout << "Вы точно хотите изменить данную характеристику (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            all_matches[match_index].data.day = new_day;
            all_matches[match_index].data.month = new_month;
            cout << "Дата изменена." << endl;
        }
        else cout << "Дата не изменена." << endl;
        break;
    }

    case 4: {
        int new_hour, new_minutes;
        cout << "Введите новое время (ЧЧ:ММ): ";
        cout << " Час :";
        cin >> new_hour;
        new_hour = check(0, 24, new_hour);
        cout << " Минуты :";
        cin >> new_minutes;
        new_minutes = check(0, 60, new_minutes);
        int confirm;
        cout << "Вы точно хотите изменить данную характеристику (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            all_matches[match_index].time.hour = new_hour;
            all_matches[match_index].time.minuts = new_minutes;
            cout << "Время изменена." << endl;
        }
        else cout << "Время не изменено." << endl;
        break;
    }
    case 5:
    {
        string new_stadium;
        cout << "Введите новый стадион проведения: ";
        getline(cin, new_stadium);
        new_stadium = check_on_digit(new_stadium);
        int confirm;
        cout << "Вы точно хотите изменить данную характеристику (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            all_matches[match_index].stadium = new_stadium;
            cout << "Стадион проведения измененён." << endl;
        }
        else  cout << "Стадио проведения  не изменён." << endl;
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
        cout << "Введите команды: ";
        getline(cin, poisk_teams);
        poisk_teams = check_on_size(poisk_teams, 4);
        for (int i = 0; i < all_matches.size(); i++)
        {
            if (all_matches[i].teams.find(poisk_teams) != string::npos)
            {
                count1++;
                if (count1 == 1)
                {
                    cout << "Результаты по командам: " << poisk_teams << endl;
                    Output_first_match();
                }
                Output_need_match(i);
            }
        }
        if (count1 == 0)
            cout << "Матчи с командой " << poisk_teams << " не найдены." << endl;
    }
    break;
    case 2:
    {
        int count2 = 0;
        string poisk_stadium;
        cout << "Введите название стадиона: ";
        getline(cin, poisk_stadium);
        poisk_stadium = check_on_size(poisk_stadium, 3);
        for (int i = 0; i < all_matches.size(); i++)
        {
            if (all_matches[i].stadium.find(poisk_stadium) != string::npos)
            {
                count2++;
                if (count2 == 1)
                {
                    cout << "Результаты по стадиону: " << poisk_stadium << endl;
                    Output_first_match();
                }
                Output_need_match(i);
            }
        }
        if (count2 == 0)
            cout << "Матчи на стадионе " << poisk_stadium << " не найдены." << endl;
    }
    break;
    case 3:
    {
        int count3 = 0;
        int poisk_day, poisk_month;
        cout << "Введите день матча: ";
        cin >> poisk_day;
        poisk_day = check_on_letters(poisk_day);
        cout << "Введите месяц матча: ";
        cin >> poisk_month;
        poisk_month = check_on_letters(poisk_month);
        for (int i = 0; i < all_matches.size(); i++)
        {
            if (poisk_day == all_matches[i].data.day && poisk_month == all_matches[i].data.month)
            {
                count3++;
                if (count3 == 1)
                {
                    cout << "Результаты по дате: " << poisk_day << "." << poisk_month << endl;
                    Output_first_match();
                }
                Output_need_match(i);
            }
        }
        if (count3 == 0)
            cout << "Матчи на дату " << poisk_day << "." << poisk_month << " не найдены." << endl;
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
    cout << "Выберите поле для сортировки:\n";
    cout << "1. Команды\n";
    cout << "2. Дата (день, месяц)\n";
    cout << "3. Время (часы, минуты)\n";
    cout << "4. Стадион проведения\n";
    cout << "5. В меню" << endl;
    cin >> choice;
    choice = check(0, 5, choice);
    switch (choice) {
    case 1:
        sort(all_matches.begin(), all_matches.end(), compare_by_teams);
        cout << "Все матчи были отсортированы по командам" << endl;
        break;
    case 2:
        sort(all_matches.begin(), all_matches.end(), compare_by_date);
        cout << "Все матчи были отсортированы по дате" << endl;
        break;
    case 3:
        sort(all_matches.begin(), all_matches.end(), compare_by_time);
        cout << "Все матчи были отсортированы по времени" << endl;
        break;
    case 4:
        sort(all_matches.begin(), all_matches.end(), compare_by_stadium);
        cout << "Все матчи были отсортированы по стадиону проведения" << endl;
        break;
    }
    if (choice != 5) Output_match();
}
extern void Output_first_match()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    get_color
        cout << "__________________________________________________________________________________________________________________________________" << endl;
    cout << "|"; other_color cout << "            Команды   "; get_color cout << "        |"; other_color
        cout << "          Стадион проведения          "; get_color cout << "|"; other_color
        cout << "      Дата     "; get_color cout << "|"; other_color
        cout << "   Время  "; get_color cout << "|         "; other_color
        cout << " Доступные билеты     "; get_color cout << "|" << endl;
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
    if (!all_matches.size()) { cout << "Нет информации о матчах" << endl; return false; }
}
extern void Get_past_match()
{
    if (!Size_of_File_match()) return;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    get_color
        cout << "__________________________________________________________________________________________________________________________________" << endl;
    cout << "|"; other_color cout << "            Команды   "; get_color cout << "        |"; other_color
        cout << "          Стадион проведения          "; get_color cout << "|"; other_color
        cout << "      Дата     "; get_color cout << "|"; other_color
        cout << "   Время  "; get_color cout << "|         "; other_color
        cout << " Проданные билеты     "; get_color cout << "|" << endl;
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
    cout << "Чтобы купить билеты на матч введите команды (пример: Динамо - Торпедо)" << endl;
    cin.ignore();
    getline(cin, teams);
    int i, tickets, show = 0;
    for (i = 0; i < all_matches.size(); i++)
        if (all_matches[i].teams.find(teams) != string::npos)
        {
            show++;
            break;
        }
    if (!show) { cout << "Таких команд нет" << endl; return; }
    if (!Gettime(i)) { cout << "Матч " << all_matches[i].teams << " уже прошёл, на него нельзя забронировать билет" << endl; return; }
    cout << "Сколько билетов вы хотите забронировать на матч " << all_matches[i].teams << " ?" << endl;
    cin >> tickets;
    tickets = check(1, 100, tickets);
    if (all_matches[i].tickets - tickets <= 0) { cout << "К сожалению на данный мачт нет билетов" << endl; return; }
    cout << "Вы точто хотите забранировать билеты (1/0) ?" << endl;
    int choise;
    cin >> choise;
    choise = check(0, 1, choise);
    if (choise == 1)
    {
        all_matches[i].tickets = all_matches[i].tickets - tickets;
        cout << (tickets == 1 ? "Билет был успешно забранирован" : "Билеты были успешно забронированы") << " на матч " << all_matches[i].teams << endl;
        Write_in_file_match();
    }
    else cout << "Вы отменили своё решение" << endl;
}
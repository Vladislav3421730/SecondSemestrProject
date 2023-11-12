#include<iostream>
#include<Windows.h>
#include<fstream>
#include<string.h>
#include"passwords and check.h"
#include "club.h"
#include<iomanip>
#include<string>
#include <vector>
#include <algorithm>
#define get_color  SetConsoleTextAttribute(console, 4);
#define other_color  SetConsoleTextAttribute(console, 9);
#define no_color SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
using namespace std;
struct staff {
    string ID;
    string FIO;
    struct Time
    {
        int year;
        int month;
    } time;
    string achivments;
    string job_title;
};
const string FILE_OF_STAFF = "file_of_staff.txt";
vector<staff> kol_of_staff;
extern void Add_staff()
{
    int number;
    cout << "Сколько работников вы хотите ввести: ";
    cin >> number;
    number = check_on_letters(number);
    for (int i = 0; i < number; i++) {
        staff* temp_staff = new staff();
        cout << "Введите информацию работника " << i + 1 << endl;
        cout << "ID работника: ";
        getline(cin, temp_staff->ID);
        cout << "ФИО работника: ";
        getline(cin, temp_staff->FIO);
        temp_staff->FIO = check_on_digit(temp_staff->FIO);
        cout << "Сколько работник провёл врмени в клубе " << endl;
        cout << " Сколько  лет: ";
        cin >> temp_staff->time.year;
        temp_staff->time.year = check(0, 100, temp_staff->time.year);
        cout << " Сколько   месяцев: ";
        cin >> temp_staff->time.month;
        temp_staff->time.month = check(0, 12, temp_staff->time.month);
        cout << "Должность в клубе :";
        getline(cin, temp_staff->job_title);
        temp_staff->job_title = check_on_digit(temp_staff->job_title);
        cout << "Достижения  и характеристика :";
        getline(cin, temp_staff->achivments);
        kol_of_staff.push_back(*temp_staff);
        delete temp_staff;
    }
}

extern void Write_in_file_staff() {
    ofstream fadd(FILE_OF_STAFF, ios::out);
    for (int i = 0; i < kol_of_staff.size(); i++) {
        fadd << kol_of_staff[i].ID << ","
            << kol_of_staff[i].FIO << ","
            << kol_of_staff[i].time.year << ","
            << kol_of_staff[i].time.month << ","
            << kol_of_staff[i].job_title << ","
            << kol_of_staff[i].achivments << endl;
    }
    fadd.close();
}
extern void copy_staff_from_file()
{
    ifstream fin(FILE_OF_STAFF);
    if (!fin.is_open())
    {
        cout << "Ошибка открытия файла " << FILE_OF_STAFF << endl;
        return;
    }
    string line;
    while (getline(fin, line))
    {
        staff* temp_staff = new staff();
        int pos = 0, prev_pos = 0;
        for (int i = 0; i < 6; i++)
        {
            pos = line.find(",", prev_pos);
            string value = line.substr(prev_pos, pos - prev_pos);
            switch (i)
            {
            case 0:
                temp_staff->ID = value;
                break;
            case 1:
                temp_staff->FIO = value;
                break;
            case 2:
                temp_staff->time.year = stoi(value);
                break;
            case 3:
                temp_staff->time.month = stoi(value);
                break;
            case 4:
                temp_staff->job_title = value;
                break;
            case 5:
                temp_staff->achivments = value;
                break;
            }
            prev_pos = pos + 1;
        }
        kol_of_staff.push_back(*temp_staff);
        delete temp_staff;
    }
    fin.close();
}
extern void Output_staff()
{
    if (!Size_of_File_staff()) return;
    Output_first_staff();
    for (int i = 0; i < kol_of_staff.size(); i++)
        Output_need_staff(i);
}
void extern print_year(int i)
{
    if (kol_of_staff[i].time.year <= 10)
    {
        if (kol_of_staff[i].time.year == 1) cout << setw(4) << kol_of_staff[i].time.year << setw(5) << " год";
        else if (kol_of_staff[i].time.year > 1 && kol_of_staff[i].time.year < 5) cout << setw(4) << kol_of_staff[i].time.year << setw(5) << " года";
        else  cout << setw(4) << kol_of_staff[i].time.year << setw(5) << " лет";
    }
    else
    {
        if (kol_of_staff[i].time.month > 10 && kol_of_staff[i].time.month < 15) cout << setw(4) << kol_of_staff[i].time.month << setw(5) << " лет";
        else  if (kol_of_staff[i].time.year % 10 == 1) cout << setw(4) << kol_of_staff[i].time.year << setw(5) << " год";
        else if (kol_of_staff[i].time.year % 10 > 1 && kol_of_staff[i].time.year % 10 < 5) cout << setw(4) << kol_of_staff[i].time.year << setw(5) << " года";
        else  cout << setw(4) << kol_of_staff[i].time.year << setw(5) << " лет";
    }
}
void extern print_month(int i)
{
    if (kol_of_staff[i].time.month <= 10)
    {
        if (kol_of_staff[i].time.month == 1) cout << setw(4) << kol_of_staff[i].time.month << setw(8) << " месяц";
        else if (kol_of_staff[i].time.month > 1 && kol_of_staff[i].time.month < 5) cout << setw(4) << kol_of_staff[i].time.month << setw(8) << " месяца";
        else  cout << setw(4) << kol_of_staff[i].time.month << setw(8) << " месяцев";
    }
    else
    {
        if (kol_of_staff[i].time.month > 10 && kol_of_staff[i].time.month < 15) cout << setw(4) << kol_of_staff[i].time.month << setw(8) << " месяцев";
        else if (kol_of_staff[i].time.month % 10 == 1) cout << setw(4) << kol_of_staff[i].time.month << setw(8) << " месяц";
        else if (kol_of_staff[i].time.month % 10 > 1 && kol_of_staff[i].time.month % 10 < 5) cout << setw(4) << kol_of_staff[i].time.month << setw(8) << " месяца";
        else  cout << setw(4) << kol_of_staff[i].time.month << setw(8) << " месяцев";
    }
}
void extern Output_need_staff(int i)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    get_color cout << "|  "; no_color cout << setw(8) << kol_of_staff[i].ID; get_color cout << " |     "; no_color cout << setw(25) << kol_of_staff[i].FIO; get_color cout << "       |  "; no_color print_year(i); print_month(i);
    get_color cout << "   |"; no_color cout << setw(30) << kol_of_staff[i].job_title; get_color cout << "|  "; no_color cout << setw(45) << kol_of_staff[i].achivments; get_color cout << "  |" << endl;
    cout << "|___________|_____________________________________|__________________________|______________________________|_________________________________________________|" << endl;
    no_color
}
void extern Output_first_staff()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    get_color
        cout << "_______________________________________________________________________________________________________________________________________________________________" << endl;
    cout << "|    "; other_color cout << "ID    "; get_color cout << " |               "; other_color cout << " ФИО                 "; get_color cout << " |      ";
    other_color cout << " Время в клубе     "; get_color cout << " |      "; other_color cout << " Должность   "; get_color cout << "           |              "; other_color cout << " Характеристика      "; get_color cout << "              | " << endl;
    cout << "|___________|_____________________________________|__________________________|______________________________|_________________________________________________|" << endl;
    no_color
}
extern void delete_staff()
{
    if (!Size_of_File_staff()) return;
    cout << "Введите ID работника которого вы хотите удалить, Если хотитее удвлить всех работников нажмите 99" << endl;
    string ID;
    getline(cin, ID);
    if (ID == "99")
    {
        int choise;
        cout << "Вы точно хотите удалить всех игроков (0/1)?" << endl;
        cin >> choise;
        choise = check(0, 1, choise);
        if (choise)
        {
            kol_of_staff.clear();
            cout << "Все работники удалены." << endl;
        }
        else cout << "Вы отменили своё решение удалить всех работников" << endl;
    }
    else
    {
        bool n = false;
        register int i;
        for (i = 0; i < kol_of_staff.size(); i++)
            if (kol_of_staff[i].ID == ID)
            {
                n = true;
                break;
            }
        if (!n) cout << "Работнки с ID " << ID << " не был найден" << endl;
        else
        {
            if (n) cout << "Вы точно хотите удалить работнкиа" << endl;
            Output_first_staff();
            Output_need_staff(i);
            int choise;
            cout << "Вы точно хотите удалить этого работника (0/1)?" << endl;
            cin >> choise;
            choise = check(0, 1, choise);
            if (choise)
            {
                kol_of_staff.erase(kol_of_staff.begin() + i);
                cout << "Работник с ID " << ID << " был удалён" << endl;
            }
            else cout << "Вы отменили своё решение" << endl;
        }
    }
}
extern void edit_staff()
{
    if (!Size_of_File_staff()) return;
    string id;
    cout << "Введите ID работника: ";
    getline(cin, id);
    int staff_index = -1;
    for (int i = 0; i < kol_of_staff.size(); i++) {
        if (kol_of_staff[i].ID == id) {
            staff_index = i;
            break;
        }
    }
    if (staff_index == -1) {
        cout << "Работник с таким ID не найден." << endl;
        return;
    }
    cout << "Выберите, какую характеристику работника вы хотите изменить:" << endl;
    cout << "1. ФИО" << endl;
    cout << "2. Время нахождения в клубе" << endl;
    cout << "3. Должность" << endl;
    cout << "4. Достижения и характеристика" << endl;
    cout << "5. В меню" << endl;
    int choice;
    cin >> choice;
    choice = check(1, 7, choice);
    switch (choice) {
    case 1:
    {
        string new_fio;
        cout << "Введите новое ФИО: ";
        getline(cin, new_fio);
        new_fio = check_on_digit(new_fio);
        int confirm;
        cout << "Вы точно хотите изменить данную характеристику (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            kol_of_staff[staff_index].FIO = new_fio;
            cout << "ФИО изменено." << endl;
        }
        else {
            cout << "ФИО не изменено." << endl;
        }

        break;
    }

    case 2: {
        int new_day, new_month, new_year;
        cout << "Введите новое время нахождения в клубе:" << endl;
        cout << " Сколько лет : ";
        cin >> new_year;
        new_year = check(0, 100, new_year);
        cout << "  Сколько месяцев: ";
        cin >> new_month;
        new_month = check(0, 12, new_month);
        int confirm;
        cout << "Вы точно хотите изменить данную характеристику (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            kol_of_staff[staff_index].time.month = new_month;
            kol_of_staff[staff_index].time.year = new_year;
            cout << "Время в клубе изменено." << endl;
        }
        else {
            cout << "время в клубе не изменено." << endl;
        }

        break;
    }
    case 3:
    {
        string new_title;
        cout << "Введите новую должность работника: ";
        getline(cin, new_title);
        int confirm;
        cout << "Вы точно хотите изменить данную характеристику (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            kol_of_staff[staff_index].job_title = new_title;
            cout << "Должность изменена." << endl;
        }
        else {
            cout << "Должность  не изменена." << endl;
        }
        break;
    }
    case 4:
    {
        string new_ac;
        cout << "Введите новую характеристку: ";
        getline(cin, new_ac);
        int confirm;
        cout << "Вы точно хотите изменить данную характеристику (1/0)? ";
        cin >> confirm;
        confirm = check(0, 1, confirm);
        if (confirm == 1) {
            kol_of_staff[staff_index].achivments = new_ac;
            cout << "Характеристика изменена." << endl;
        }
        else {
            cout << "Характеристика не изменена." << endl;
        }
        break;
    }
    }
}
extern void poisk_staff(int n)
{
    switch (n)
    {
    case 1:
    {
        register int count1 = 1;
        string poisk_ID;
        cout << "Введите ID работника, которого вы хотите найти" << endl;
        getline(cin, poisk_ID);
        poisk_ID = check_on_size(poisk_ID, 3);
        for (register int i = 0; i < kol_of_staff.size(); i++)
        {
            if (kol_of_staff[i].ID.find(poisk_ID) != string::npos)
            {
                count1--;
                if (!count1)
                {
                    cout << "Результаты по ID: " << poisk_ID << endl;
                    Output_first_staff();
                }
                Output_need_staff(i);
            }
        }
        if (count1 == 1) cout << "Работник с ID " << poisk_ID << " не был найден." << endl;
    }break;
    case 2:
    {
        register int count2 = 1;
        string poisk_FIO;
        cout << "Введите ФИО работника, которого вы хотите найти" << endl;
        getline(cin, poisk_FIO);
        poisk_FIO = check_on_size(poisk_FIO, 5);
        for (register int i = 0; i < kol_of_staff.size(); i++)
        {
            if (kol_of_staff[i].FIO.find(poisk_FIO) != string::npos)
            {
                count2--;
                if (!count2)
                {
                    cout << "Результаты по ФИО: " << poisk_FIO << endl;
                    Output_first_staff();
                }
                Output_need_staff(i);
            }
        }
        if (count2 == 1) cout << "Работник с ФИО " << poisk_FIO << " не был найден." << endl;
    }break;
    case 3:
    {
        register int count3 = 1;
        string poisk_title;
        cout << "Введите должность работника, которого вы хотите найти" << endl;
        getline(cin, poisk_title);
        poisk_title = check_on_size(poisk_title, 4);
        for (register int i = 0; i < kol_of_staff.size(); i++)
        {
            if (kol_of_staff[i].job_title.find(poisk_title) != string::npos)
            {
                count3--;
                if (!count3)
                {
                    cout << "Результаты по должности: " << poisk_title << endl;
                    Output_first_staff();
                }
                Output_need_staff(i);
            }
        }
        if (count3 == 1) cout << "Работник с должностью " << poisk_title << " не был найден." << endl;
    }break;
    }
}
bool compare_by_FIO(const staff& a, const staff& b) {
    return a.FIO < b.FIO;
}

bool compare_by_kol_of_year(const staff& a, const staff& b) {
    return a.time.year < b.time.year;
}

bool compare_by_kol_of_title(const staff& a, const staff& b) {
    return a.job_title < b.job_title;
}
extern void sort_staff()
{
    if (!Size_of_File_staff()) return;
    int choice;
    cout << "Выберите поле для сортировки:\n";
    cout << "1. ФИО\n";
    cout << "2. Время в клубе ( по годам )\n";
    cout << "3. Должность\n";
    cout << "4. В меню" << endl;
    cin >> choice;
    choice = check(0, 4, choice);
    switch (choice) {
    case 1:
        sort(kol_of_staff.begin(), kol_of_staff.end(), compare_by_FIO);
        cout << "Все работники были отсортированы по ФИО" << endl;
        break;
    case 2:
        sort(kol_of_staff.begin(), kol_of_staff.end(), compare_by_kol_of_year);
        cout << "Все работники были отсортированы по времни в клубе" << endl;
        break;
    case 3:
        sort(kol_of_staff.begin(), kol_of_staff.end(), compare_by_kol_of_title);
        cout << "Все работники были отсортированы по должности" << endl;
        break;
    }
    if (choice != 4) Output_staff();
}
extern bool Size_of_File_staff()
{
    if (!kol_of_staff.size()) { cout << "Нет информации о работниках" << endl; return false; }
}

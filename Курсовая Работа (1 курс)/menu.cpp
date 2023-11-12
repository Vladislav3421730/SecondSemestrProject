#include<iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include"passwords and check.h"
#include"menu.h"
#include"club.h"
#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void d(short x, short y)
{
	SetConsoleCursorPosition(h, { x,y });
}
void normal_size()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 16;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	ConsoleCursorVisible(true, 25);
	cout << endl << endl;
}
void another_size()
{
	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	font.nFont = 0;
	GetCurrentConsoleFontEx(h, FALSE, &font);
	font.dwFontSize.X = 16;
	font.dwFontSize.Y = 24;
	wcscpy_s(font.FaceName, L"Consolas");
	ConsoleCursorVisible(false, 100);
	SetCurrentConsoleFontEx(h, FALSE, &font);

}
void show_menu_for_user()
{
	system("cls");
	string T[] = { "Информация об игроках", "Информация о штабе", "Информация о матчах","Редактировать личный кабинет","Выход" };
	char aT = 0;
	char c;
	another_size();
	while (true)
	{
		char x = 50, y = 12;
		d(x, y);
		for (char i = 0; i < size(T); i++)
		{
			if (i == aT)  SetConsoleTextAttribute(h, FOREGROUND_RED);
			else  SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			d(x, y++);
			cout << T[i] << endl;
		}
		c = _getch();
		if (c == -32) c = _getch();
		switch (c)
		{
		case ESC:
			exit(0);
		case UP:
			if (aT > 0)	--aT;
			break;
		case DOWN:
			if (aT < size(T) - 1)	++aT;
			break;
		case ENTER:
			switch (aT)
			{
			case 0:
			{
				d(x, y);
				system("cls");
				menu_for_user_player();
				break;
			}
			case 1:
			{

				d(x, y);
				system("cls");
				menu_for_user_staff();
				break;
			}
			case 2:
			{
				system("cls");
				d(x, y);
				menu_for_user_match();
				break;
			}
			case 3:
			{
				system("CLS");
				normal_size();
				EDIT();
				system("pause");
				system("CLS");
				another_size();
				break;
			}
			case 4:
			{
				system("cls");
				normal_size();
				SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				Write_in_file_accaunts();
				exit(0);
				break;
			}
			default: cout << "" << (char)c << endl;
			}
		}
	}
}
void show_menu_for_admin()
{


	int choise;
	cout << "1. Информация об игроках" << endl;
	cout << "2. Информация о тренерском штабе" << endl;
	cout << "3. Информация о матчах" << endl;
	cout << "4. Просмотр всех записей пользователй" << endl;
	cout << "5. Выйти из программы" << endl;
	cin >> choise;
	choise = check(1, 5, choise);
	system("cls");
	switch (choise)
	{
	case 1: menu_for_admin_player(); break;
	case 2: menu_for_admin_staff(); break;
	case 3: menu_for_admin_match();  break;
	case 4: show_users(); system("pause"); system("cls"); show_menu_for_admin(); break;
	case 5: Write_in_file_accaunts(); return;
	}
	system("cls");
}
void menu_for_admin_player()
{

	int choise;
	do
	{
		cout << "Меню для работы с игроками" << endl;
		cout << "1-Добавление" << endl;
		cout << "2-Редактирование" << endl;
		cout << "3-Поиск" << endl;
		cout << "4-Удаление" << endl;
		cout << "5-Сортировка" << endl;
		cout << "6-Вывод" << endl;
		cout << "7-В меню" << endl;
		cin >> choise;
		choise = check(1, 7, choise);
		switch (choise)
		{
		case 1:Add_players(); break;
		case 2:edit_players(); break;
		case 3:
			cout << "Выберете параметр по которому вы хотите найти игрока" << endl;
			menu_for_poisk_players(); break;
		case 4: delete_players();	break;
		case 5: sort_players(); break;
		case 6:  Output_players();  break;
		case 7:	Write_in_file_player(); system("cls"); show_menu_for_admin(); break;
		}
	} while (choise != 7);
}

void menu_for_user_player()
{
	system("CLS");
	another_size();
	string T[] = { "Вывести игроков","Вывести топ 6 игроков по системе гол+пас","Поиск", "Сортировка", "В меню" };
	char aT = 0;
	char c;
	while (true)
	{
		char x = 50, y = 12;
		d(x, y);
		for (char i = 0; i < size(T); i++)
		{
			if (i == aT)  SetConsoleTextAttribute(h, FOREGROUND_RED);
			else  SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			d(x, y++);
			cout << T[i] << endl;
		}
		c = _getch();
		if (c == -32) c = _getch();
		switch (c)
		{
		case ESC:
			exit(0);
		case UP:
			if (aT > 0)	--aT;
			break;
		case DOWN:
			if (aT < size(T) - 1)	++aT;
			break;
		case ENTER:
			switch (aT)
			{
			case 0:
			{
				d(x, y);
				normal_size();
				Output_players();
				system("pause");
				system("CLS");
				another_size();
				menu_for_user_player();
				break;
			}
			case 1:
			{
				d(x, y);
				normal_size();
				Output_top_six();
				system("pause");
				system("CLS");
				another_size();
				menu_for_user_player();
				break;
			}
			case 2:
			{

				d(x, y);
				normal_size();
				cout << "Выбкрете по какому параметру вы хотите найти игрока" << endl;
				menu_for_poisk_players();
				system("pause");
				system("cls");
				another_size();
				menu_for_user_player();
				break;
			}
			case 3:
			{

				d(x, y);
				normal_size();
				sort_players();
				system("pause");
				system("cls");
				another_size();
				menu_for_user_player();
				break;
			}
			case 4:
			{
				show_menu_for_user();
				exit(0);
				break;
			}
			default: cout << "" << (char)c << endl;
			}
		}
	}
	system("CLS");

}
void  menu_for_user_staff()
{
	system("CLS");
	string T[] = { "Вывести штаб работников","Поиск", "Сортировка", "В меню" };
	char aT = 0;
	char c;

	while (true)
	{
		char x = 50, y = 12;
		d(x, y);
		for (char i = 0; i < size(T); i++)
		{
			if (i == aT)  SetConsoleTextAttribute(h, FOREGROUND_RED);
			else  SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			d(x, y++);
			cout << T[i] << endl;
		}
		c = _getch();
		if (c == -32) c = _getch();
		switch (c)
		{
		case ESC:
			exit(0);
		case UP:
			if (aT > 0)	--aT;
			break;
		case DOWN:
			if (aT < size(T) - 1)	++aT;
			break;
		case ENTER:
			switch (aT)
			{
			case 0:
			{

				d(x, y);
				normal_size();
				Output_staff();
				system("pause");
				system("CLS");
				another_size();
				menu_for_user_staff();
				break;
			}
			case 1:
			{

				d(x, y);
				normal_size();
				cout << "Выберете по какому параметру вы хотите найти работника" << endl;
				menu_for_poisk_staff();
				system("pause");
				system("CLS");
				another_size();
				menu_for_user_staff();
				break;
			}
			case 2:
			{

				d(x, y);
				normal_size();
				sort_staff();
				system("pause");
				system("cls");
				another_size();
				menu_for_user_staff();
				break;
			}
			case 3:
			{
				show_menu_for_user();
				break;
			}
			default: cout << "" << (char)c << endl;
			}
		}
	}
}
void menu_for_user_match()
{
	system("CLS");
	string T[] = { "Вывести","Поиск", "Сортировка", "Вывести прошедшие матчи","Купить билет на матч","В меню" };
	char aT = 0;
	char c;
	another_size();
	while (true)
	{
		char x = 50, y = 12;
		d(x, y);
		for (char i = 0; i < size(T); i++)
		{
			if (i == aT)  SetConsoleTextAttribute(h, FOREGROUND_RED);
			else  SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			d(x, y++);
			cout << T[i] << endl;
		}
		c = _getch();
		if (c == -32) c = _getch();
		switch (c)
		{
		case ESC:
			exit(0);
		case UP:
			if (aT > 0)	--aT;
			break;
		case DOWN:
			if (aT < size(T) - 1)	++aT;
			break;
		case ENTER:
			switch (aT)
			{
			case 0:
			{

				d(x, y);
				normal_size();
				Get_future_match();
				system("pause");
				system("cls");
				another_size();
				menu_for_user_match();
				break;
			}
			case 1:
			{

				d(x, y);
				normal_size();
				cout << "Выберете по какому параметру вы хотите найти матч" << endl;
				menu_for_poisk_match();
				system("pause");
				system("cls");
				another_size();
				menu_for_user_match();
				break;
			}
			case 2:
			{

				d(x, y);
				normal_size();
				sort_match();
				system("pause");
				system("cls");
				another_size();
				menu_for_user_match();
				break;
			}
			case 3:
			{
				d(x, y);
				normal_size();
				cout << "Прошедшие матчи" << endl;
				Get_past_match();
				system("pause");
				system("cls");
				another_size();
				menu_for_user_match();
				break;
			}
			case 4:
			{
				d(x, y);
				normal_size();
				buy_tickets();
				system("pause");
				system("cls");
				another_size();
				menu_for_user_match();
				break;
			}
			case 5:
			{
				show_menu_for_user();
				exit(0);
				break;
			}
			default: cout << "" << (char)c << endl;
			}
		}
	}
}
void menu_for_admin_staff()
{
	int choise;
	do
	{
		cout << "Меню для работы с персоналом" << endl;
		cout << "1-Добавление" << endl;
		cout << "2-Редактирование" << endl;
		cout << "3-Поиск" << endl;
		cout << "4-Удаление" << endl;
		cout << "5-Сортировка" << endl;
		cout << "6-Вывод" << endl;
		cout << "7-В меню" << endl;
		cin >> choise;
		choise = check(1, 7, choise);
		switch (choise)
		{
		case 1:Add_staff(); break;
		case 2:edit_staff(); break;
		case 3:
			cout << "Выберете параметр по которому вы хотите найти работника" << endl;
			menu_for_poisk_staff(); break;
		case 4: delete_staff();	break;
		case 5: sort_staff(); break;
		case 6: Output_staff();  break;
		case 7:	Write_in_file_staff(); system("cls"); show_menu_for_admin(); break;
		}
	} while (choise != 7);
}
extern void  menu_for_poisk_staff()
{
	if (!Size_of_File_staff()) return;
	int choise;
	cout << "1-ID" << endl;
	cout << "2-ФИО" << endl;
	cout << "3-Должность" << endl;
	cout << "4-В меню" << endl;
	cin >> choise;
	choise = check(1, 8, choise);
	switch (choise)
	{
	case 1:poisk_staff(1); break;
	case 2:poisk_staff(2); break;
	case 3:poisk_staff(3); break;

	}
}
int menu_for_admin_match()
{

	int choise;
	do
	{
		cout << "Меню для работы с матчами" << endl;
		cout << "1-Добавление" << endl;
		cout << "2-Редактирование" << endl;
		cout << "3-Поиск" << endl;
		cout << "4-Удаление" << endl;
		cout << "5-Сортировка" << endl;
		cout << "6-Вывод" << endl;
		cout << "7-В меню" << endl;
		cin >> choise;
		choise = check(1, 7, choise);
		switch (choise)
		{
		case 1:Add_match(); break;
		case 2:edit_match(); break;
		case 3:
			cout << "Выберете параметр по которому вы хотите найти работника" << endl;
			menu_for_poisk_match(); break;
		case 4: delete_match();	break;
		case 5: sort_match(); break;
		case 6: Output_match();  break;
		case 7:Write_in_file_match(); system("cls"); show_menu_for_admin();
		}
	} while (choise != 7);
	return choise;
}
extern void menu_for_poisk_players()
{
	if (!Size_of_File()) return;
	int choise;
	cout << "1-ID" << endl;
	cout << "2-ФИО" << endl;
	cout << "3-Дата рождения" << endl;
	cout << "4-Количество матчей" << endl;
	cout << "5-Забитые шайбы" << endl;
	cout << "6-Передачи" << endl;
	cout << "7-Количество штрафных минут" << endl;
	cout << "8-В меню" << endl;
	cin >> choise;
	choise = check(1, 8, choise);
	switch (choise)
	{
	case 1:poisk_players(1); break;
	case 2:poisk_players(2); break;
	case 3:poisk_players(3); break;
	case 4:poisk_players(4); break;
	case 5:poisk_players(5); break;
	case 6:poisk_players(6); break;
	case 7:poisk_players(7); break;
	}
}
extern void menu_for_poisk_match()
{
	if (!Size_of_File_match()) return;
	int choise;
	cout << "1-Команды" << endl;
	cout << "2-Стадион" << endl;
	cout << "3-Дата (НН.ММ)" << endl;
	cout << "4-В меню" << endl;
	cin >> choise;
	choise = check(1, 4, choise);
	switch (choise)
	{
	case 1:poisk_match(1); break;
	case 2:poisk_match(2); break;
	case 3:poisk_match(3); break;
	}
}

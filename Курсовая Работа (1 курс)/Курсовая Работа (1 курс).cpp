#include<iostream>
#include<Windows.h>
#include"passwords and check.h"
#include"menu.h"
#include"club.h"
using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Добро пожаловать!!!" << endl;
	copy_players_from_file();
	copy_staff_from_file();
	copy_match_from_file();

	switch (show_menu_for_registr())
	{
	case 1:
		cout << "Добро пожаловать в меню для пользователя" << endl;
		Sleep(500);

		show_menu_for_user(); system("cls"); break;
	case 2:
		system("cls");
		cout << "Добро пожаловать в меню для администратора" << endl;
		show_menu_for_admin(); break;
	}
}

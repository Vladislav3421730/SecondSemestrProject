#include<iostream>
#include<Windows.h>
#include<fstream>
#include<string.h>
#include"passwords and check.h"
#include <conio.h>
#include <string>
#include<vector>
#include<algorithm>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
using namespace std;
const string FILE_OF_ADMIN = "file_admins.txt";
const string  FILE_OF_USERS = "file_users.txt";
struct accaunts_of_admin
{
	string new_password_admin, new_login_admin;
}; vector<accaunts_of_admin> admin;
struct accaunts_of_user
{
	string new_password_user, new_login_user;
};
vector<accaunts_of_user> user;
int show_menu_for_registr()
{
	int n;
	copy_accaunts_from_file();
	cout << "1. Войти как пользователь" << endl;
	cout << "2. Войти как администратор" << endl;
	cout << "3. Зарегистрироваться" << endl;
	cout << "4. Выйти из программы" << endl;
	cout << "На данный момент зарегистрировано пользователей: " << user.size() << endl;
	cout << "На данный момент зарегистрировано администраторов: " << admin.size() << endl;
	cin >> n;
	n = check(1, 5, n);
	switch (n)
	{
	case 1:
		if (INPUT_FOR_USERS()) return n;
		else
		{
			cout << "Данные введены неверно" << endl;
			system("pause");
			system("cls");
			show_menu_for_registr();
		}break;
	case 2:
		if (INPUT_FOR_ADMIN())	return n;
		else
		{
			cout << "Данные введены неверно" << endl;
			system("pause");
			system("cls");
			show_menu_for_registr();
		}break;
	case 3:REGISTRATION();
		system("pause");
		system("cls");
		show_menu_for_registr(); break;
	case 4: Write_in_file_accaunts(); return 0;
	}
}
void show_users()
{
	cout << "Все пользователи:" << endl;
	cout << "____________________________________________________________" << endl;
	cout << "|                     Логин               |       Хеш      |" << endl;
	cout << "|_________________________________________|________________|" << endl;
	for (register int i = 0; i < user.size(); i++)
	{
		cout << "|     " << setw(30) << user[i].new_login_user << "      |" << "    " << setw(10) << user[i].new_password_user << "  |" << endl;
		cout << "|_________________________________________|________________|" << endl;
	}

}
int check(int left_range, int right_range, int number)
{
	while (!isNumberNumeric() || number > right_range || number < left_range)
	{

		cout << "Введено некоректное значение" << endl;
		cin >> number;
	}
	return number;
}
string check_on_digit(string str)
{
	while (str.find_first_of("0123456789") != string::npos)
	{
		system("cls");
		cout << "Вы ввели неправильное значение,  в данном поле не могут находиться цифры" << endl;
		cout << "Соберите 7 очков в игре змейка, чтобы ввести нормальное значение данного поля" << endl;
		cout << "Правила :" << endl;
		cout << "1. Нельзя соприкасаться со стенками" << endl;
		cout << "2. Нельзя соприкасаться с другими частями змейки" << endl;
		cout << "3. Управлять нужно при помощи w,a,s,d" << endl;
		cout << "Если хотите выйти нажмите e" << endl;
		system("pause");
		snake();
		cout << "Введите значение данного поля, но без цифр" << endl;
		getline(cin, str);
	}
	return str;
}
bool isNumberNumeric()
{

	if (cin.get() == '\n')
	{

		return true;

	}
	else
	{
		cin.clear();
		cin.ignore(256, '\n');
		return false;
	}
}
int check_on_letters(int n)
{
	while (!isNumberNumeric() || n < 0)
	{
		cout << "Введено некоректное значение" << endl;
		cin >> n;
	}
	return n;
}
string check_on_size(string str, int n)
{
	while (str.size() < n)
	{
		cout << "Вы ввели малое количество символов для поиска" << endl;
		getline(cin, str);
	}
	return str;
}
void ConsoleCursorVisible(bool show, short size)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
void snake()
{
	system("cls");
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	bool gameover = false;
	enum edirectoin { ST0P = 0, LEFT, RIGHT, UP, DOWN };
	edirectoin dir;
	int y, x, fx, fy;
	int s = 0;
	int t = 0, ty[100], tx[100];
	dir = ST0P;
	x = 15;
	y = 10;
	fx = rand() % 15;
	fy = rand() % 15;
	while (!gameover && s < 7)
	{

		for (int i = 0; i < 30; i++)
		{
			SetConsoleTextAttribute(hStdOut, 8);
			cout << '#';
		}
		cout << endl;

		for (int i = 0; i < 15; i++)
		{

			for (int j = 0; j < 29; j++)
			{

				if (j == 0 || j == 28)
				{
					SetConsoleTextAttribute(hStdOut, 8);
					cout << '#';
					SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				if (i == y && j == x)
				{
					SetConsoleTextAttribute(hStdOut, 5);
					cout << '0';
					SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				else if (i == fy && j == fx)
				{
					SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
					cout << '@';
					SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				}
				else
				{
					bool p = false;
					for (int k = 0; k < t; k++)
						if (tx[k] == j && ty[k] == i)
						{
							p = true;
							SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
							cout << 'o';
							SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
						}
					if (!p) cout << ' ';
				}

			}
			cout << endl;
		}
		for (int i = 0; i < 30; i++)
		{
			SetConsoleTextAttribute(hStdOut, 8);
			cout << '#';
			SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}
		cout << endl;
		cout << "Счёт:" << s << endl;

		COORD coord;
		coord.X = 0;
		coord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		ConsoleCursorVisible(false, 100);

		if (_kbhit)
		{
			switch (_getch())
			{
			case 'a': dir = LEFT; break;
			case 's': dir = DOWN; break;
			case 'w': dir = UP; break;
			case 'd': dir = RIGHT; break;
			case 'e': gameover = true; break;
			}
		}
		int px = tx[0];
		int py = ty[0];
		int p2x, p2y;
		tx[0] = x;
		ty[0] = y;

		for (int i = 1; i < t; i++)
		{
			p2x = tx[i];
			p2y = ty[i];
			tx[i] = px;
			ty[i] = py;
			px = p2x;
			py = p2y;
		}
		switch (dir)
		{
		case LEFT: x--;  break;
		case UP: y--; break;
		case RIGHT: x++; break;
		case DOWN: y++; break;
		}

		if (x == fx && y == fy)
		{
			s++;
			fx = rand() % 25;
			fy = rand() % 15;
			t++;
		}

		if (x == -1 || x == 28 || y == -1 || y == 15) gameover = true;
		for (int i = 0; i < t; i++)
			if (tx[i] == x && ty[i] == y) gameover = true;

	}
	if (s == 7)
	{
		system("cls");
		ConsoleCursorVisible(true, 25);
		cout << "Поздравляем!!! Вам удалось выиграть" << endl;
		system("pause");
	}
	else
	{
		system("cls");
		cout << "Попробуйте ещё раз" << endl;
		system("pause");
		snake();
	}
	system("cls");
}

string vvod(string password)
{
	password = "";
	char ch;
	while ((ch = _getch()) != '\r') {
		if (ch == '\b') {
			if (password.length() > 0) {
				password.pop_back();
				cout << "\b \b";
			}
		}
		else {
			password += ch;
			cout << "*";
		}
	}cout << endl;
	return password;
}
string encryptPassword(string to_encrypt)
{
	const int shift = 3;
	for (int i = 0; i < to_encrypt.length(); i++) {
		to_encrypt[i] = (to_encrypt[i] - ' ' - shift + ('~' - ' ' + 1)) % ('~' - ' ') + ' ';

	}
	return to_encrypt;
}

bool INPUT_FOR_USERS()
{
	string login, password;
	cout << "Логин: ";
	getline(cin, login);
	cout << "Пароль: ";
	password = vvod(password);
	password = encryptPassword(password);
	bool choise = false;
	for (register int i = 0; i < user.size(); i++)
		if (login == user[i].new_login_user && password == user[i].new_password_user) choise = true;
	if (!choise) return false;
	else return true;
}
bool INPUT_FOR_ADMIN()
{
	string login, password;
	cout << "Логин: ";
	getline(cin, login);
	cout << "Пароль: ";
	password = vvod(password);
	password = encryptPassword(password);
	bool choise = false;
	for (register int i = 0; i < admin.size(); i++)
		if (login == admin[i].new_login_admin && password == admin[i].new_password_admin) choise = true;
	if (!choise) return false;
	else return true;

}
void REGISTRATION()
{
	int n;
	cout << "Выберете как вы хотите зарегистрироваться" << endl;
	cout << "1-Как пользователь" << endl;
	cout << "2-Как администратор" << endl;
	cout << "3-Отмена регистрации" << endl;
	cin >> n;
	n = check(1, 3, n);
	if (n == 1)
	{
		accaunts_of_user* user1 = new accaunts_of_user();
		cout << "Новый логин пользователя: ";
		getline(cin, user1->new_login_user);
		cout << "Новый пароль пользователя: ";
		user1->new_password_user = "";
		char ch;
		while ((ch = _getch()) != '\r')
		{
			if (ch == '\b') {
				if (user1->new_password_user.length() > 0) {
					user1->new_password_user.pop_back();
					cout << "\b \b";
				}
			}
			else {
				user1->new_password_user += ch;
				cout << "*";
			}
		}cout << endl;
		const int shift = 3;
		for (int i = 0; i < user1->new_password_user.length(); i++)
		{
			user1->new_password_user[i] = (user1->new_password_user[i] - ' ' - shift + ('~' - ' ' + 1)) % ('~' - ' ') + ' ';

		}
		user.push_back(*user1);
		delete user1;
		cout << "Новый пользователь зарегистрирован" << endl;

	}
	else if (n == 2)
	{
		accaunts_of_admin* admin1 = new accaunts_of_admin();
		string special_password;
		int i = 0;
		cout << "Если вы хотите зарегестрироваться как администротор нужен специальный пароль самого хоккейного клуба" << endl;
		special_password = vvod(special_password);
		while (special_password != "q1w2e3" && i < 5)
		{
			cout << "Специальный пароль неверный" << endl;
			special_password = vvod(special_password);
			i++;
		}
		if (i == 5)
		{
			cout << "Вам не удалось ввести специальный пароль хоккейного клуба" << endl;
		}
		else
		{
			cout << "Новый логин администратора: ";
			getline(cin, admin1->new_login_admin);
			cout << "Новый пароль администратора: ";
			admin1->new_password_admin = "";
			char ch;
			while ((ch = _getch()) != '\r')
			{
				if (ch == '\b') {
					if (admin1->new_password_admin.length() > 0) {
						admin1->new_password_admin.pop_back();
						cout << "\b \b";
					}
				}
				else {
					admin1->new_password_admin += ch;
					cout << "*";
				}
			}cout << endl;
			const int shift = 3;
			for (int i = 0; i < admin1->new_password_admin.length(); i++)
			{
				admin1->new_password_admin[i] = (admin1->new_password_admin[i] - ' ' - shift + ('~' - ' ' + 1)) % ('~' - ' ') + ' ';

			}
			admin.push_back(*admin1);
			delete admin1;
			cout << "Новый администротор зарегестрирован" << endl << endl;
		}
	}


}
void Write_in_file_accaunts()
{

	ofstream fadd(FILE_OF_USERS, ios::out);
	for (int i = 0; i < user.size(); i++) {
		fadd << user[i].new_login_user << ","
			<< user[i].new_password_user << endl;
	}
	fadd.close();
	ofstream file(FILE_OF_ADMIN, ios::out);
	for (int i = 0; i < admin.size(); i++) {
		file << admin[i].new_login_admin << ","
			<< admin[i].new_password_admin << endl;
	}
	file.close();

}
void copy_accaunts_from_file()
{
	if (!user.empty() || !admin.empty()) return;
	ifstream fin(FILE_OF_USERS);
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла " << FILE_OF_USERS << endl;
		return;
	}
	string line;
	while (getline(fin, line)) {
		accaunts_of_user* user1 = new accaunts_of_user();
		int pos = 0, prev_pos = 0;
		for (int i = 0; i < 2; i++)
		{
			pos = line.find(",", prev_pos);
			string value = line.substr(prev_pos, pos - prev_pos);
			switch (i)
			{
			case 0:user1->new_login_user = value; break;
			case 1:user1->new_password_user = value; break;
			}
			prev_pos = pos + 1;
		}
		user.push_back(*user1);
		delete user1;
	}
	fin.close();
	ifstream file(FILE_OF_ADMIN);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла " << FILE_OF_ADMIN << endl;
		return;
	}
	string line1;
	while (getline(file, line1)) {
		accaunts_of_admin* admin1 = new accaunts_of_admin();
		int pos1 = 0, prev_pos1 = 0;
		for (int i = 0; i < 2; i++)
		{
			pos1 = line1.find(",", prev_pos1);
			string value = line1.substr(prev_pos1, pos1 - prev_pos1);
			switch (i)
			{
			case 0:
				admin1->new_login_admin = value; break;
			case 1:
				admin1->new_password_admin = value; break;
			}
			prev_pos1 = pos1 + 1;
		}
		admin.push_back(*admin1);
		delete admin1;
	}
	file.close();
}
void EDIT()
{
	cout << "Чтобы изменить данные нужно ввести логин и пароль" << endl;
	string login, password;
	cout << "Логин: ";
	getline(cin, login);
	cout << "Пароль: ";
	password = vvod(password);
	password = encryptPassword(password);
	bool  choise = false;
	int i;
	for (i = 0; i < user.size(); i++)
	{
		if (login == user[i].new_login_user && password == user[i].new_password_user)
		{
			choise = true;
			break;
		}
	}
	if (!choise)
	{
		cout << "Данные введены неверно" << endl;
		return;
	}
	cout << "Что вы хотите изменить?" << endl;
	cout << "1. Логин" << endl;
	cout << "2. Пароль" << endl;
	cout << "3. Отмена" << endl;
	int choice;
	cin >> choice;
	choice = check(1, 3, choice);
	if (choice == 1)
	{
		cout << "Введите ваш новый логин " << endl;
		string new_login;
		getline(cin, new_login);
		int choise;
		cout << "Вы точно хотите изменить логин (0/1)?" << endl;
		cin >> choise;
		choise = check(0, 1, choise);
		if (choise)
		{
			user[i].new_login_user = new_login;
			cout << "Логин изменён на " << new_login << endl;
		}
		else cout << "Вы отменили своё решение " << endl;
	}
	else if (choice == 2)
	{
		cout << "Введите ваш новый пароль " << endl;
		string new_password;
		new_password = vvod(new_password);
		int choice;
		cout << "Вскоре вам будет выслан код для подтверждения изменения пароля" << endl;
		string code = "ASDFG12346GHUKMKN758739LMJHBGHYJV";
		char code1[6];
		srand(time(NULL));
		for (int i = 0; i < 5; i++)
		{
			code1[i] = code[rand() % code.size()];
		}
		code1[5] = '\0';
		Sleep(3000);
		cout << "Специальный код: " << code1 << endl;
		string attempt;

		getline(cin, attempt);
		int sh = 0;
		while (sh < 5 && attempt != code1)
		{
			cout << "Код введён неверно" << endl;
			cout << "Повторно введите высланный пароль: ";
			getline(cin, attempt);
			sh++;
		}
		if (sh == 5)
		{
			cout << "Вы не смогли ввести высланный пароль" << endl;
			return;
		}
		cout << "Вы точно хотите изменить пароль (0/1)?" << endl;
		cin >> choice;
		choice = check(0, 1, choice);
		if (choice)
		{
			user[i].new_password_user = new_password;
			const int shift = 3;
			int a = i;
			for (int i = 0; i < user[a].new_password_user.length(); i++)
			{
				user[a].new_password_user[i] = (user[a].new_password_user[i] - ' ' - shift + ('~' - ' ' + 1)) % ('~' - ' ') + ' ';

			}
			cout << "Пароль изменён на " << new_password << endl;
		}
		else {
			cout << "Вы отменили своё решение " << endl;
		}

	}

}
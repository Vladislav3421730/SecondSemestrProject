#pragma once
extern int show_menu_for_registr();
extern int check(int left_range, int right_range, int number);
extern bool isNumberNumeric();
extern bool INPUT_FOR_USERS();
extern bool INPUT_FOR_ADMIN();
extern void REGISTRATION();
extern std::string check_on_digit(std::string str);
extern int check_on_letters(int n);
extern void copy_accaunts_from_file();
extern std::string check_on_size(std::string str, int n);
extern void Write_in_file_accaunts();
extern void EDIT();
extern void snake();
extern void show_users();
extern void ConsoleCursorVisible(bool show, short size);
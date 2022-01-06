#pragma once
#include<list>
#include<vector>
#include<map>
#include <string>
using namespace std;

struct Elem
{
	string name; //пунк меню
	string level; // текущий уровень меню
	//string level_next; // следующий уровень меню
	//string level_prev; // предыдущий уровень меню
	int command; // исполняемая команда
	string file_name; // имя запускаемого файла

};



class Menu
{
	vector<Elem> menu_items; //перечень всех пунктов меню
	vector<Elem> level_menu; //подменю
	//map<string, string> commmand; // список исполняемых команд <команда, исполняемый фаил>
	int pos = 0;// текущая позиция в меню
	int last_pos = 1;// предыдущая позиция меню
public:
	Menu() {};
	//Menu(map<string, string> commmand);
	~Menu() {}
	void GetLevel(string &level); //выбираю из общей кучи нужные элементы и возвращаю их адреса
	auto GetPOS() 
	{
		auto it = level_menu[pos];
		return it; 
	}
	auto Getpos() { return pos; }
	void showLevel();
	void add(string _name, string _level, int _command, string _file_name = "menu");
	//void read_menu(string file);
	//void write_menu();
	void change_position(int key);
	//int key_handler(vector<Elem*> items); // 
};


#pragma once
#include<list>
#include<vector>
#include<map>
#include <string>
using namespace std;

struct Elem
{
	string name; //���� ����
	string level; // ������� ������� ����
	//string level_next; // ��������� ������� ����
	//string level_prev; // ���������� ������� ����
	int command; // ����������� �������
	string file_name; // ��� ������������ �����

};



class Menu
{
	vector<Elem> menu_items; //�������� ���� ������� ����
	vector<Elem> level_menu; //�������
	//map<string, string> commmand; // ������ ����������� ������ <�������, ����������� ����>
	int pos = 0;// ������� ������� � ����
	int last_pos = 1;// ���������� ������� ����
public:
	Menu() {};
	//Menu(map<string, string> commmand);
	~Menu() {}
	void GetLevel(string &level); //������� �� ����� ���� ������ �������� � ��������� �� ������
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


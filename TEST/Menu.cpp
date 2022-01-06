#include "Menu.h"
#include "Main.h"

//Menu::Menu(map<string, string> commmand)
//{
//	
//}

void Menu::GetLevel(string &level)
{
	level_menu.clear(); // обнуляем прошлый список подменю
	pos = 0; // обнуляем текущую позиция в меню
	last_pos = 1; // обнуляем предыдущую позиция меню
	for (auto& elem : menu_items)
	{
		if (elem.level == level) level_menu.emplace_back(elem); // обновляем список подменю
	}
}

void Menu::showLevel()
{
	system("cls");
	for (auto i = level_menu.begin(); i != level_menu.end(); i++) //выводим пункты меню
	{
		if (i == level_menu.begin()) setColor(0, 4);
		else setColor(0, 15);
		cout << i->name << endl;
	}
}

void Menu::add(string _name, string _level, int _command, string _file_name)
{
	Elem tmp;
	tmp.name = _name; 
	tmp.level = _level;
	//tmp.level_next = _level_next;
	//tmp.level_prev = _level_prev;
	tmp.command = _command;
	tmp.file_name = _file_name;
	menu_items.push_back(tmp);
}

void Menu::change_position(int key)
{
	last_pos = pos;
	switch (key)
	{
	case UP: pos--;
		break;
	case DOWN: pos++;
		break;
	}
	if (pos == level_menu.size()) pos = 0;
	else if (pos < 0) pos = level_menu.size() - 1;
	// изменение положения курсора
	GotoXY(0, last_pos);
	setColor(0, 15);
	cout << level_menu[last_pos].name;
	GotoXY(0, pos);
	setColor(0, 4);
	cout << level_menu[pos].name;
	setColor(0, 15);
}

//int Menu::key_handler(vector<Elem*> items)
//{				
//	//выводим пункты меню
//	system("cls");
//		
//	for (auto i = items.front(); i <= items.back(); i++) //выводим пункты меню
//	{
//		if (i == items.begin()) setColor(0, 4);
//		else setColor(0, 15);
//		cout << *() << endl;
//	}
//	 
//	 //обработчик кнопок
//	int m = 0;
//	int pos = 0, last_pos = 0;// переменная для позиционирования курсора
//	do
//	{
//		last_pos = pos;
//		m = _getch();
//		if (_kbhit()) m = _getch(); //смотрим есть что нибудь в потоке т.к. функциональные клавиши выдают двойной символ
//		switch (m)
//		{
//		case UP: pos--;
//			break;
//		case DOWN: pos++;
//			break;
//		}
//		if (pos == items.size()) pos = 0;
//		else if (pos < 0) pos = items.size() - 1;
//		// изменение положения курсора
//		GotoXY(0, last_pos);
//		setColor(0, 15);
//		cout << items[last_pos].name;
//		GotoXY(0, pos);
//		setColor(0, 4);
//		cout << items[pos].name;
//	} while (m != 13);	
//	return pos;
//}



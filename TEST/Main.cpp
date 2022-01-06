#include "Main.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	bool work = true;
	Menu menu;
	User::LoadShortList();
	 //проверка на зарегистрированного админа
	bool admin = false;
	for (auto& elem : User::GetshortListUsers())
	{
		if (elem.is_admin == true) { admin = true; break; }
	}




	//auto result = find_if(User::GetshortListUsers().begin(), User::GetshortListUsers().end(), [](const shotListUsers& us) // находим в списке нашего юзера
	//	{
	//		return us.is_admin == true;
	//	});
	//если нет то добавляю дефолтного
	if (!admin)
	{
		Admin adm;
		string str = "admin";
		adm.SetLogin(str);
		adm.SetPassword(str);
		adm.saveToFile();
		adm.~Admin();
	}

	//LEVEL 1
				//name->level->command->file_name
	menu.add("Авторизация", "1", AUTHORIZATION);	 	//AUTHORIZATION
	menu.add("Регистрация", "1", REGISTRATION);			//REGISTRATION
	menu.add("Выход", "1", EXIT); 						//EXIT
	


	

	string pos = "1";
	
	
	do
	{
		menu.GetLevel(pos);
		menu.showLevel();
		int m = 0;
		do
		{
			m = _getch();
			if (_kbhit()) m = _getch(); //смотрим есть что нибудь в потоке т.к. функциональные клавиши выдают двойной символ
			menu.change_position(m);
		} while (m != ENTER);
		system("cls");
		
		// вытягиваю команду и сравниваю ее с перечнем команд
		switch (menu.GetPOS().command)
		{
		case AUTHORIZATION:
		{
			autorization();
			break;
		}
		case REGISTRATION:
		{
			registration();
			//pos = "1";
			break;
		}
		case EXIT: //"Выход из программы"
		{
			work = false;
			break;
		}
		}		
	} while (work);
	
 }


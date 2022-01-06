#include "Main.h"




int getXcoord()
{
	CONSOLE_SCREEN_BUFFER_INFO info_x;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_x);
	return info_x.dwCursorPosition.X;
}

int getYcoord()
{
	CONSOLE_SCREEN_BUFFER_INFO info_y;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
	return info_y.dwCursorPosition.Y;
}


void GotoXY(int X, int Y)
{
	COORD coord = { X, Y };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, coord);
}
void setColor(int Background, int Text)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((Background << 4) | Text));
}

void readTems(Menu& tems, int command) // command это PASS_EXAM/ADD_CATEGORY/DEL_CATEGORY/ADD_TEST/CHANGE_TESTS
{
	string temp_str, name, file_name; //Наименование разделя/экзамена и путь к файлу
	int pos = 0; // счетчик разделов
	//Menu tems; //создаем меню для тем
	fstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		file.open("syst.txt", ios::in);
		getline(file, temp_str);
		tems.add("Назад", "1", EXIT); //выход
		while (!file.eof())
		{			
			if (temp_str == "#")
			{
				pos++;
				getline(file, name);
				//getline(file, file_name);
				tems.add(name, "1", NEXT); //добавляем тему
				temp_str = "1" + to_string(pos);
				tems.add("Назад", temp_str, BACK);
				getline(file, temp_str);
				if (temp_str == "##")
				{
					while (temp_str != "#" && !file.eof())
					{
						getline(file, name);
						getline(file, file_name);
						temp_str = "1" + to_string(pos);
						tems.add(name, temp_str, command, file_name); //добавляем экзамены
						getline(file, temp_str);
					}
				}
				//getline(file, temp_str);
			}
			
		}
		file.close();
	}
	catch (const ifstream::failure& ex)
	{
		cout << "Ошибка открытия файла" << endl;
		cout << ex.what() << endl;
		ex.code();
	}
}

void passExam(Student &stud)
{
	Menu menuExam;
	readTems(menuExam, PASS_EXAM);
	string pos = "1";
	bool work = true;
	do
	{
		menuExam.GetLevel(pos);
		menuExam.showLevel();
		int m = 0;
		do
		{
			m = _getch();
			if (_kbhit()) m = _getch(); //смотрим есть что нибудь в потоке т.к. функциональные клавиши выдают двойной символ
			menuExam.change_position(m);
		} while (m != ENTER);
		system("cls");
		switch (menuExam.GetPOS().command)
		{
		case NEXT:
			pos += to_string(menuExam.Getpos()); //прибавляю уровень
			break;
		case BACK:
			pos = menuExam.GetPOS().level;
			pos.pop_back();
			break;
		case PASS_EXAM:
			stud.StartExam(menuExam.GetPOS().name, menuExam.GetPOS().file_name);
			system("pause");	
			break;
		case EXIT: //"Выход из программы"		
			work = false;
			break;
		}
	} while (work);	
}

void registration()
{
	string name, surname, middle_name, adress, phohe_number, login, password;
	cout << "Логин: ";
	getline(cin, login);			
	cout << "Пароль: ";
	getline(cin, password);

	int a = User::welcome(login, password);
	if (a == -2)
	{
		cout << "Имя: ";
		getline(cin, name);
		cout << "Фамилия: ";
		getline(cin, surname);
		cout << "Отчество: ";
		getline(cin, middle_name);
		cout << "Адресс: ";
		getline(cin, adress);
		cout << "Телефон: ";
		getline(cin, phohe_number);
		Student stud(name, surname, middle_name, adress, phohe_number, login, password);
		stud.posNow(a);
		stud.saveToFile();
		system("cls");
		cout << "Спасибо за регистрацию!\n\n\n";
	}
	else cout << "Пользователь с таким логином зарегистрирован\n\n\n";
	
	system("pause");
}

void autorization()
{
	string login, password;
	cout << "Логин: ";
	getline(cin, login);
	cout << "Пароль: ";
	getline(cin, password);
	int OK = User::welcome(login, password);
	if (OK < 0) { system("cls"); cout << "Не верный логин или пароль\n\n"; system("pause"); }
	else
	{
		bool admin = false;
		for (auto& elem : User::GetshortListUsers())
		{
			if (elem.pos_in_file == OK) { admin = elem.is_admin; break; }
		}
		//auto result = find_if(User::GetshortListUsers().begin(), User::GetshortListUsers().end(), [&](const shotListUsers& us) // находим в списке нашего юзера
		//{
		//	return us.pos_in_file == OK;
		//});
		admin == true ? adminMenu(OK) : studentMenu(OK);
	}
}

void studentMenu(int pos_in_file)
{
	system("cls");
	Student std; // создаем студента
	std.LoadData(pos_in_file); // загружаю из файла данные о студенте
	Menu menuStud;
	menuStud.add("История", "1", HISTORY); //HISTORY, UNFINISHED_EXAMS, PASS_EXAM
	menuStud.add("Завершить экзамен", "1", UNFINISHED_EXAMS); //UNFINISHED_EXAMS
	menuStud.add("Сдать экзамен", "1", PASS_EXAM); //PASS_EXAM
	menuStud.add("Выход", "1", EXIT);
	string pos = "1";
	bool work = true;
	do
	{
		menuStud.GetLevel(pos);
		menuStud.showLevel();
		int m = 0;
		do
		{
			m = _getch();
			if (_kbhit()) m = _getch(); //ñìîòðèì åñòü ÷òî íèáóäü â ïîòîêå ò.ê. ôóíêöèîíàëüíûå êëàâèøè âûäàþò äâîéíîé ñèìâîë
			menuStud.change_position(m);
		} while (m != ENTER);
		system("cls");
		switch (menuStud.GetPOS().command)
		{
		case HISTORY:
			history(std);
			system("pause");
			break;
		case UNFINISHED_EXAMS:
			unfinishedExam(std);
			system("pause");
			break;
		case PASS_EXAM:
			passExam(std);
			break;
		case EXIT: //"Âûõîä èç ïðîãðàììû"		
			work = false;
			break;
		}
	} while (work);
}

void history(Student& stud)
{
	if (stud.GetCompleteExam().empty() && stud.GetIncompleteExam().empty())
	{
		cout << "Пора начинать\n\n\n";
	}
	else
	{
		cout << setw(24) << left << "Экзамен";
		cout << setw(12) << left << "Статус";
		cout << setw(8) << left << "Оценка";
		cout << setw(9) << left << "Процент";
		cout << setw(16) << left << "Верных ответов";
		cout << setw(21) << left << "Не верных ответов";
		cout << setw(26) << left << "Дата сдачи" << endl;
		for (auto& elem : stud.GetCompleteExam())
		{
			cout << setw(24) << left << elem.GetExamName();
			cout << setw(12) << left << "Сдано";
			cout << setw(8) << left << elem.GetGrade();
			cout << setw(9) << left << elem.GetPersent();
			cout << setw(16) << left << elem.GetCorrectAnswer();
			cout << setw(21) << left << elem.GetIncorrectAnswer();
			cout << setw(26) << left << elem.GetDate() << endl;
		}
		for (auto& elem : stud.GetIncompleteExam())
		{
			cout << setw(24) << left << elem.GetExamName();
			cout << setw(12) << left << "Не окончен" << endl;
		}
	}	
}

void unfinishedExam(Student& stud)
{
	Menu menuInc;
	for (auto& elem : stud.GetIncompleteExam())
	{
		menuInc.add(elem.GetExamName(), "1", PASS_EXAM, elem.GetWay()); //HISTORY, UNFINISHED_EXAMS, PASS_EXAM
	}
	menuInc.add("Выход", "1", EXIT);
	string pos = "1";
	bool work = true;
	do
	{
		menuInc.GetLevel(pos);
		menuInc.showLevel();
		int m = 0;
		do
		{
			m = _getch();
			if (_kbhit()) m = _getch(); //ñìîòðèì åñòü ÷òî íèáóäü â ïîòîêå ò.ê. ôóíêöèîíàëüíûå êëàâèøè âûäàþò äâîéíîé ñèìâîë
			menuInc.change_position(m);
		} while (m != ENTER);
		system("cls");
		switch (menuInc.GetPOS().command)
		{
		case PASS_EXAM:
			stud.StartExam(menuInc.GetPOS().name, menuInc.GetPOS().file_name);
			break;
		case EXIT: //"Âûõîä èç ïðîãðàììû"		
			work = false;
			break;
		}		
	} while (work);
}

void adminMenu(int pos_in_file)
{
	Admin adm;
	if(pos_in_file >= 0) adm.LoadData(pos_in_file); // загружаю из файла данные о студенте
	Menu menuAdm;
	menuAdm.add("Изменить учётную запись", "1", CHANGE_PASS); 		//CHANGE_PASS
	menuAdm.add("Управление пользователями", "1", NEXT);
	menuAdm.add("Просмотр статистики", "1", NEXT);
	menuAdm.add("Управление тестированием", "1", NEXT);
	menuAdm.add("Назад", "1", EXIT);
	//Level 11
	menuAdm.add("Создать учётную запись", "11", ADD_USER);
	menuAdm.add("Удальть учётную запись", "11", DEL_USER);
	menuAdm.add("Редактировать учётную запись", "11", CHANGE_USER);
	menuAdm.add("Назад", "11", BACK);
	//LEVEL 12
	menuAdm.add("Общая статистика по категориям", "12", STATISTIC_CATEGORY);
	menuAdm.add("Статистика по тестам", "12", STATISTIC_TEST);
	menuAdm.add("Статистика по пользователям", "12", STATISTIC_USER);
	menuAdm.add("Назад", "12", BACK);
	//LEVEL 13
	menuAdm.add("Добавить категорию", "13", ADD_CATEGORY);
	menuAdm.add("Удалить категорию", "13", DEL_CATEGORY);
	menuAdm.add("Добавить тест", "13", ADD_TEST);
	menuAdm.add("Удалить тест", "13", DEL_TEST);
	menuAdm.add("Редактировать тест", "13", CHANGE_TESTS);
	menuAdm.add("Назад", "13", BACK);
	string pos = "1";
	bool work = true;
	do
	{
		menuAdm.GetLevel(pos);
		menuAdm.showLevel();
		int m = 0;
		do
		{
			m = _getch();
			if (_kbhit()) m = _getch(); //смотрим есть что нибудь в потоке т.к. функциональные клавиши выдают двойной символ
			menuAdm.change_position(m);
		} while (m != ENTER);
		system("cls");
		switch (menuAdm.GetPOS().command)
		{
		case NEXT:
			pos += to_string(menuAdm.Getpos()); //прибавляю уровень
			break;
		case BACK:
			pos = menuAdm.GetPOS().level;
			pos.pop_back();
			break;
		case CHANGE_PASS:
			changePassAdmin(adm);
			break;
		case ADD_USER:
		case DEL_USER:
		case CHANGE_USER:
		case STATISTIC_CATEGORY:
		case STATISTIC_TEST:
		case STATISTIC_USER:
		case ADD_CATEGORY:
		case DEL_CATEGORY:
		case ADD_TEST:
		case DEL_TEST:
		case CHANGE_TESTS:
			cout << "Раздел в разработке\n\n";
			system("pause");
			break;
		case EXIT: //"Выход из программы"		
			work = false;
			break;
		}
	} while (work);
}

void changePassAdmin(Admin &adm)
{
	string login, password, tmp;
	cout << "Логин: ";
	getline(cin, login);
	cout << "Пароль: ";
	getline(cin, password);
	adm.SetLogin(login);
	adm.SetPassword(password);
	adm.saveToFile();
}
#include "Student.h"

Student::Student(string _name, string _surname, string _middle_name, string _adress, string _phohe_number, string _login, string _password) : User(_login, _password)
{
	name = _name;
	surname = _surname;
	middle_name = _middle_name;
	adress = _adress;
	phohe_number = _phohe_number;
}


void Student::write(fstream &base)
{
	int size;
	size = this->login.length();
	base.write((char*)&size, sizeof(int)); //Записываем количество символов в логине
	base.write((char*)this->login.c_str(), size * sizeof(char)); //Записываем логин
	size = this->password.length();
	base.write((char*)&size, sizeof(int)); //Записываем количество символов в пароле
	base.write((char*)this->password.c_str(), size * sizeof(char)); //Записываем пароль
	size = this->name.length();
	base.write((char*)&size, sizeof(int)); //Записываем количество символов в имени
	base.write((char*)this->name.c_str(), size * sizeof(char)); //Записываем имя

	size = this->surname.length();
	base.write((char*)&size, sizeof(int)); //Записываем количество символов в фамилию
	base.write((char*)this->surname.c_str(), size * sizeof(char)); //Записываем фамилию
	size = this->middle_name.length();
	base.write((char*)&size, sizeof(int)); //Записываем количество символов в отчестве
	base.write((char*)this->middle_name.c_str(), size * sizeof(char)); //Записываем отчество
	size = this->adress.length();
	base.write((char*)&size, sizeof(int)); //Записываем количество символов в адрес
	base.write((char*)this->adress.c_str(), size * sizeof(char)); //Записываем адрес
	size = this->phohe_number.length();
	base.write((char*)&size, sizeof(int)); //Записываем количество символов в телефон
	base.write((char*)this->phohe_number.c_str(), size * sizeof(char)); //Записываем телефон
	size = this->complete_exam.size();
	base.write((char*)&size, sizeof(int)); //Записываем количество элементов в массиве
	
	for (auto& elem : complete_exam)
	{
		//pos = base.tellp();
		elem.writeExam(base); //пишем оконченные экзамены
		//pos = base.tellg();
	}
	size = this->incomplete_exam.size();
	base.write((char*)&size, sizeof(int)); //Записываем количество элементов в массиве
	for (auto& elem : incomplete_exam)
	{
		//pos = base.tellp();
		elem.writeExam(base); //пишем неоконченные экзамены
	}
}



int Student::saveToFile()
{
	int pos = this->pos_now;	
	int size, poss = 0;
	//int poss; // позиция в файле базы данных
	fstream base, tmp_base;
	base.exceptions(ifstream::badbit | ifstream::failbit);
	tmp_base.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		base.open("data_base.txt", ios::out | ios::binary | ios::in | ios::app | ios::ate); // без ate не хочет выдавать позицию
		if (pos >= 0)
		{
			tmp_base.open("tmp_base.txt", ios::out | ios::binary | ios::trunc);
			base.seekp(0, ios::beg);
			while (base.tellp() != pos)
			{
				char ch;
				base.get(ch);
				tmp_base.put(ch);
				//base.read((char*)&c, sizeof(char)); //читаем бит из файла
				//tmp_base.write((char*)c, sizeof(char)); // записываем этот бит в темповый файл
			}
			write(tmp_base);// запись структуры
			poss = tmp_base.tellp();
			poss = changeUsersPos(login, poss);
			saveToFileShortList();			
			//poss = base.tellp(); // запоминаем место положения начала следующей структуры 
			if (poss >= 0)
			{
				base.seekp(poss, ios::beg);
				while (base.peek() != EOF)
				{
					char ch;
					base.get(ch);
					tmp_base.put(ch);
					//base.read((char*)&c, sizeof(char)); //читаем бит из файла
					//tmp_base.write((char*)c, sizeof(char)); // записываем этот бит в темповый файл
				}
			}		
			
			base.close(); 
			tmp_base.close();
			remove("data_base.txt");
			if (rename("tmp_base.txt", "data_base.txt") != 0)
				cout << "Error!\n Couldn't rename file. Сheck old and new filename...\n\n";
			//else
				//cout << "Ok...\n\n";
			//rename("temp.txt", "data_base.txt"); 

		}
		else
		{
			poss = base.tellp();
			write(base);// запись структуры в конце файла
			shotListUsers us;
			us.log = this->login;
			us.pass = this->password;
			us.pos_in_file = poss;
			us.is_admin = false;
			users.push_back(us);			
			saveUserPosInFile(us);
			poss = base.tellp();
			base.close();
		}		
		
		return poss;
	}
	catch (const ifstream::failure& ex)
	{
		cout << "Ошибка открытия файла data_base.txt" << endl;
		cout << ex.what() << endl;
		ex.code();
	}	
}

void Student::LoadData(int pos)
{
	this->pos_now = pos;
	int temp;
	char* str;
	//char a;
	int poss;
	fstream base;
	base.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{		
		base.open("data_base.txt", ios::in | ios::binary);	
		base.seekp(pos, ios::beg);
		//base.read((char*)&temp, sizeof(int)); // читаем признак студент / админ
		base.read((char*)&temp, sizeof(int)); // читаем размер логина
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // читаем логин
		str[temp] = '\0';
		this->login = str;
		base.read((char*)&temp, sizeof(int)); // читаем размер пароля
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // читаем пароль
		str[temp] = '\0';
		this->password = str;
		base.read((char*)&temp, sizeof(int)); // читаем размер имя
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // читаем имя
		str[temp] = '\0';
		this->name = str;
		base.read((char*)&temp, sizeof(int)); // читаем размер фамилию
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // читаем фамилию
		str[temp] = '\0';
		this->surname = str;
		base.read((char*)&temp, sizeof(int)); // читаем размер отчества
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // читаем отчество
		str[temp] = '\0';
		this->middle_name = str;
		base.read((char*)&temp, sizeof(int)); // читаем размер адрес
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // читаем адрес
		str[temp] = '\0';
		this->adress = str;
		base.read((char*)&temp, sizeof(int)); // читаем размер телефон
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // читаем телефон
		str[temp] = '\0';
		this->phohe_number = str;
		base.read((char*)&temp, sizeof(int)); // читаем размер списка оконченных экзаменов
		for (int i = 0; i < temp; i++)
		{
			CompleteExam cmp;
			//poss = base.tellp();
			cmp.readExam(base); // читаем список оконченных экзаменов
			this->complete_exam.push_back(cmp);
		}
		base.read((char*)&temp, sizeof(int)); // читаем размер списка неоконченных экзаменов
		for (int i = 0; i < temp; i++)
		{
			IncompleteExam inc;
			//poss = base.tellp();
			inc.readExam(base);
			this->incomplete_exam.push_back(inc); // читаем список неоконченных экзаменов
		}
		base.close();
	}
	catch (const ifstream::failure& ex)
	{
		cout << "Ошибка открытия файла data_base.txt" << endl;
		cout << ex.what() << endl;
		ex.code();
		system("pause");
	}
}

void Student::StartExam(string name, string file)
{
	vector<question> q;
	IncompleteExam exam(name); //создаем версию незаконченного экзамена
	exam.SetWay(file); //запоминаем место расположения теста
	auto it = find_if(incomplete_exam.begin(), incomplete_exam.end(), [&](IncompleteExam& exam) // проверяем есть ли тест в незаконченных
		{
			return exam.GetExamName() == name;
		});

	if (it == incomplete_exam.end())
	{
		exam.selectionQuestion(file); // перемешиваем и выбираем необходимое количество вопросов
		//q = exam.readQuestion(file); // считываем из файла необходимые вопросы
	}
	
	else
	{
		exam = *it;
		incomplete_exam.erase(it);
	}
	
	
	
	q = exam.readQuestion(file); // считываем из файла необходимые вопросы
	bool c = exam.startTest(q); //запускаем тестирование
	system("cls");
	if (c) // если ответили на все вопросы
	{
		//создаем временный объект зданого экзамена
		CompleteExam complete(exam.GetExamName(), exam.GetCorrectAnswer(), exam.GetIncorrectAnswer());
		this->complete_exam.push_back(complete); // добавляем в список успешных экзаменов
		//выводим информацию об успехах
		cout << setw(24) << "Тест: " << complete.GetExamName() << endl;
		cout << setw(24) << "Верных ответов: " << complete.GetCorrectAnswer() << endl;
		cout << setw(24) << "Неверных ответов: " << complete.GetIncorrectAnswer() << endl;
		cout << setw(24) << "Процент верных ответов: " << complete.GetPersent() << endl;
		cout << setw(24) << "Оценка: " << complete.GetGrade() << endl;
		cout << setw(24) << "Дата сдачи экзамена: " << complete.GetDate(); //дата
	}
	else
	{
		cout << "Тест не окончен!" << endl;
		this->incomplete_exam.push_back(exam);

		
	}
	
	saveToFile(); //перезапись файла
}




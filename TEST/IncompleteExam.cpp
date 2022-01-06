#include "IncompleteExam.h"

//IncompleteExam::IncompleteExam(IncompleteExam& ex)
//{
//	exam = ex.exam;
//	correct_answer = ex.correct_answer;
//	incorrect_answer = ex.incorrect_answer;
//	num_question = ex.num_question;
//}

IncompleteExam& IncompleteExam::operator=(const IncompleteExam& right)
{
	//проверка на самоприсваивание
	if (this == &right) {
		return *this;
	}
	exam = right.exam;
	correct_answer = right.correct_answer;
	incorrect_answer = right.incorrect_answer;
	num_question = right.num_question;
	return *this;
}

void IncompleteExam::selectionQuestion(string qwestion_file)
{
	srand(time(NULL)); // для рандома
	int oll_question_size{ 0 }; //общее количество вопросов
	int test_question_size{ 0 }; // количество экзаминационных вопросов
	fstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		file.open(qwestion_file, ios::in);
		if (!file) { perror("file_open_error"); exit(0); }
		file >> oll_question_size;//считываем общее количество вопросов
		file.ignore(); // пропуск символа ‘/n’, оставшегося в файле после считывания числа
		file >> test_question_size; //считываем количество экзаминационных вопросов
		file.close();
		num_question.resize(oll_question_size); // распределяем память под все вопросы
		generate_n(num_question.begin(), num_question.size(), addNumberFrom(1)); //заполняем список номерами вопросов
		//int i = 0;
		//for (auto& elem : num_question) //заполняем список номерами вопросов
		//{
		//	elem = i + 1;
		//	i++;
		//}
		random_shuffle(begin(num_question), end(num_question)); // хаотично разбрасываем вопросы
		num_question.resize(test_question_size); //обрезаем список до необходимого тесту размера
		sort(begin(num_question), end(num_question)); //сортируем  попорядку для облегчения считывания
	}
	catch (const ifstream::failure& ex)
	{
		cout << "Ошибка открытия файла" << endl;
		cout << ex.what() << endl;
		ex.code();
	}
}

vector<question> IncompleteExam::readQuestion(string qwestion_file)
{
	int oll_question_size{ 0 }; //общее количество вопросов
	int test_question_size{ 0 }; // количество экзаминационных вопросов
	vector<question> test_question;
	fstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		int temp_int; // времянка для считывания чисел
		//bool temp_bool; // времянка для считывания признака верности ответа
		string temp_str; // времянка для считывания строк	
		file.open(qwestion_file, ios::in);
		file >> oll_question_size;//считываем общее количество вопросов
		file.ignore(); // пропуск символа ‘/n’, оставшегося в файле после считывания числа
		file >> test_question_size; //считываем количество экзаминационных вопросов
		file.ignore(); // пропуск символа ‘/n’, оставшегося в файле после считывания числа
		//question temp_qestion; // времянка для структуры вопроса
		if (!num_question.empty()) test_question_size = num_question.size();
		//bool temp_bool; // времянка для считывания признака верности ответа
		int i = 0;
		getline(file, temp_str); //считываем следующую строку
		while (!file.eof() && test_question_size > 0)
		{
			if (temp_str == "##") // проверяем признак следующего вопроса
			{
				file >> temp_int; // считываем номер вопроса
				file.ignore();
				if (temp_int == num_question[i]) // если номера совпадают то считываем
				{
					question temp_question;
					getline(file, temp_str);
					//string tmp_qestion = temp_str; // переменная для хранения вопроса
					temp_question.question_ = temp_str; // добавляем в структуру вопрос
					//map<string, bool> temp_map; // сюда помещаем ответы
					vector<answer> answers;
					getline(file, temp_str);
					while (temp_str != "##")
					{
						answer temp;
						if (temp_str[0] == '+') temp.true_answer = true;
						else temp.true_answer = false; //вытягиваем признак ответа верно/неверно
						//temp_bool = temp_str[0]; //вытягиваем признак ответа верно/неверно
						//temp.true_answer = temp_str[0]; //вытягиваем признак ответа верно/неверно
						temp_str[0] = ' ';	//заменяем на пробел
						temp.text = temp_str;
						answers.push_back(temp); // добавляем вопрос с признаком				
						//temp_map.empplace(temp_str, temp_bool); // добавляем вопрос с признаком
						getline(file, temp_str);
					}

					temp_question.answers = answers; // добавляем в структуру ответы
					test_question.push_back(temp_question); // добавляем задание в список
					test_question_size--; // уменшаем счетчик заданий теста
					i++;
					continue;
				}
				getline(file, temp_str);
				continue;
			}
			getline(file, temp_str);
		}
		file.close();
		return test_question;
	}
	catch (const ifstream::failure& ex)
	{
		cout << "Ошибка открытия файла" << endl;
		cout << ex.what() << endl;
		ex.code();
	}
}

bool IncompleteExam::startTest(vector<question>& test_question)
{
	reverse(num_question.begin(), num_question.end());
	for (auto elem = test_question.begin(); elem != test_question.end(); elem++)//(auto& elem : test_question)
	{
		system("cls");
		bool exit = false;
		cout << elem->question_ << endl; // печатаем вопрос
		int size = elem->answers.size(); // количество ответов в вопросе. чтобы постоянно к ней не обращаться
		//выводим пункты меню		
		int shift_y = getYcoord(); //захватываем координату по Y для смещения положения ответов
		for (auto it = elem->answers.begin(); it != elem->answers.end(); it++) //выводим ответы
		{
			if (it != elem->answers.begin()) setColor(0, 15);
			else setColor(0, 4);
			cout << "  " << it->text << endl;
		}
		int shift_key = getYcoord(); //захватываем координату по Y для смещения положения ответов
		//Выводим клавиши выхода и продолжения
		GotoXY(3, shift_key + 3);
		cout << "S-->Завершить";
		GotoXY(20, shift_key + 3);
		cout << "N-->Далее";
		// обработчик кнопок
		int m = 0;
		int pos = 0, last_pos = 0;// переменная для позиционирования курсора
		bool nex_step = false; // Переменная для прохода далее
		do
		{
			last_pos = pos;
			m = _getch();
			if (_kbhit()) m = _getch(); //смотрим есть что нибудь в потоке т.к. функциональные клавиши выдают двойной символ
			switch (m)
			{
			case UP: pos--;
				break;
			case DOWN: pos++;
				break;
			case ENTER:
				elem->answers[pos].student_answer = !elem->answers[pos].student_answer; // инвертируем ответ
				//menu_copy[pos].second = !menu_copy[pos].second; //выставляем ответы
				GotoXY(1, pos + shift_y);
				//if (menu_copy[last_pos].second == true) cout << "+";
				if (elem->answers[pos].student_answer == true) cout << "+"; //ставим/снимаем признак правильности ответа
				else cout << " ";
				break;
			}
			if (pos == size) pos = 0;
			else if (pos < 0) pos = size - 1;
			// изменение положения курсора
			GotoXY(2, last_pos + shift_y);
			setColor(0, 15);
			cout << elem->answers[last_pos].text;
			GotoXY(2, pos + shift_y);
			setColor(0, 4);
			cout << elem->answers[pos].text;
			if (m == 's' || m == 'S') //досрочный выход
			{

				m = 'n'; // выход из цикла
				exit = true;

			}

		} while (m != 'n' && m != 'N');

		if (exit == false)
		{
			//сравнение ответов
			compare_answers(*elem);
			num_question.pop_back(); // выталкиваем вопрос из списка
		}
		else
		{
			elem = test_question.end() - 1; //преждевременный выход
			reverse(num_question.begin(), num_question.end()); //переворачиваем обратно чтобы потом не мучатся
			return false;
		}

		setColor(0, 15);		
	}
	return true;
}



void IncompleteExam::compare_answers(question& qwestion)
{
	for (auto& elem : qwestion.answers)
	{
		if (elem.true_answer == elem.student_answer) correct_answer++;
		else incorrect_answer++;
	}
}

void IncompleteExam::writeExam(fstream &file)
{
	int size;
	size = exam.size();
	file.write((char*)&size, sizeof(int)); // пишем размер названия экзамена
	file.write((char*)exam.c_str(), size * sizeof(char)); // пишем названия экзамена
	size = way.size();
	file.write((char*)&size, sizeof(int)); // пишем размер пути файла
	file.write((char*)way.c_str(), size * sizeof(char)); // пишем путь к файлу
	file.write((char*)&correct_answer, sizeof(int)); // количество верных ответов
	file.write((char*)&incorrect_answer, sizeof(int)); // количество не верных ответов
	size = num_question.size();
	file.write((char*)&size, sizeof(int)); //// пишем размер массива номеров оставшихся вопросов для теста
	for (auto it = num_question.begin(); it != num_question.end(); it++)
	{
		file.write((char*)&(*it), sizeof(int)); //пишем номера оставшихся вопросов для теста
	}	
}

void IncompleteExam::readExam(fstream &file)
{
	int temp;
	char* name, *way;
	/*fstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{*/
		/*file.open("data_base.txt", ios::in | ios::binary);
		file.seekg(pos, ios::beg);*/
		file.read((char*)&temp, sizeof(int));
		name = new char[temp + 1];
		file.read((char*)name, temp * sizeof(char));
		name[temp] = '\0';
		this->exam = name;
		delete[]name;
		file.read((char*)&temp, sizeof(int));
		way = new char[temp + 1];
		file.read((char*)way, temp * sizeof(char));
		way[temp] = '\0';
		this->way = way;
		delete[] way;
		file.read((char*)&this->correct_answer, sizeof(int));//считываем верные ответы
		file.read((char*)&this->incorrect_answer, sizeof(int)); //считываем неверные ответы
		file.read((char*)&temp, sizeof(int)); //читаем размер массива с оставшимися вопросами
		int qw; //временная переменная для считывания номеров вопросов
		for (int i = 0; i < temp; i++)
		{
			file.read((char*)&qw, sizeof(int)); //читаем номер оставшегося вопроса
			this->num_question.push_back(qw); // добавляем его в массив
		}
		/*file.close();
	}
	catch (const ifstream::failure& ex)
	{
		cout << "Ошибка открытия файла" << endl;
		cout << ex.what() << endl;
		ex.code();
		system("pause");
	}*/
}



////IncompleteExam::IncompleteExam(string exam, int correct_answer, int incorrect_answer) : Exams(exam, correct_answer, incorrect_answer)
////{
////
////}

int IncompleteExam::getXcoord()
{
	CONSOLE_SCREEN_BUFFER_INFO info_x;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_x);
	return info_x.dwCursorPosition.X;
}

int IncompleteExam::getYcoord()
{
	CONSOLE_SCREEN_BUFFER_INFO info_y;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
	return info_y.dwCursorPosition.Y;
}

void IncompleteExam::GotoXY(int X, int Y)
{
	COORD coord = { X, Y };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, coord);
}

void IncompleteExam::setColor(int Background, int Text)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((Background << 4) | Text));
}

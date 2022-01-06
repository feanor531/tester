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
	//�������� �� ����������������
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
	srand(time(NULL)); // ��� �������
	int oll_question_size{ 0 }; //����� ���������� ��������
	int test_question_size{ 0 }; // ���������� ��������������� ��������
	fstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		file.open(qwestion_file, ios::in);
		if (!file) { perror("file_open_error"); exit(0); }
		file >> oll_question_size;//��������� ����� ���������� ��������
		file.ignore(); // ������� ������� �/n�, ����������� � ����� ����� ���������� �����
		file >> test_question_size; //��������� ���������� ��������������� ��������
		file.close();
		num_question.resize(oll_question_size); // ������������ ������ ��� ��� �������
		generate_n(num_question.begin(), num_question.size(), addNumberFrom(1)); //��������� ������ �������� ��������
		//int i = 0;
		//for (auto& elem : num_question) //��������� ������ �������� ��������
		//{
		//	elem = i + 1;
		//	i++;
		//}
		random_shuffle(begin(num_question), end(num_question)); // �������� ������������ �������
		num_question.resize(test_question_size); //�������� ������ �� ������������ ����� �������
		sort(begin(num_question), end(num_question)); //���������  ��������� ��� ���������� ����������
	}
	catch (const ifstream::failure& ex)
	{
		cout << "������ �������� �����" << endl;
		cout << ex.what() << endl;
		ex.code();
	}
}

vector<question> IncompleteExam::readQuestion(string qwestion_file)
{
	int oll_question_size{ 0 }; //����� ���������� ��������
	int test_question_size{ 0 }; // ���������� ��������������� ��������
	vector<question> test_question;
	fstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		int temp_int; // �������� ��� ���������� �����
		//bool temp_bool; // �������� ��� ���������� �������� �������� ������
		string temp_str; // �������� ��� ���������� �����	
		file.open(qwestion_file, ios::in);
		file >> oll_question_size;//��������� ����� ���������� ��������
		file.ignore(); // ������� ������� �/n�, ����������� � ����� ����� ���������� �����
		file >> test_question_size; //��������� ���������� ��������������� ��������
		file.ignore(); // ������� ������� �/n�, ����������� � ����� ����� ���������� �����
		//question temp_qestion; // �������� ��� ��������� �������
		if (!num_question.empty()) test_question_size = num_question.size();
		//bool temp_bool; // �������� ��� ���������� �������� �������� ������
		int i = 0;
		getline(file, temp_str); //��������� ��������� ������
		while (!file.eof() && test_question_size > 0)
		{
			if (temp_str == "##") // ��������� ������� ���������� �������
			{
				file >> temp_int; // ��������� ����� �������
				file.ignore();
				if (temp_int == num_question[i]) // ���� ������ ��������� �� ���������
				{
					question temp_question;
					getline(file, temp_str);
					//string tmp_qestion = temp_str; // ���������� ��� �������� �������
					temp_question.question_ = temp_str; // ��������� � ��������� ������
					//map<string, bool> temp_map; // ���� �������� ������
					vector<answer> answers;
					getline(file, temp_str);
					while (temp_str != "##")
					{
						answer temp;
						if (temp_str[0] == '+') temp.true_answer = true;
						else temp.true_answer = false; //���������� ������� ������ �����/�������
						//temp_bool = temp_str[0]; //���������� ������� ������ �����/�������
						//temp.true_answer = temp_str[0]; //���������� ������� ������ �����/�������
						temp_str[0] = ' ';	//�������� �� ������
						temp.text = temp_str;
						answers.push_back(temp); // ��������� ������ � ���������				
						//temp_map.empplace(temp_str, temp_bool); // ��������� ������ � ���������
						getline(file, temp_str);
					}

					temp_question.answers = answers; // ��������� � ��������� ������
					test_question.push_back(temp_question); // ��������� ������� � ������
					test_question_size--; // �������� ������� ������� �����
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
		cout << "������ �������� �����" << endl;
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
		cout << elem->question_ << endl; // �������� ������
		int size = elem->answers.size(); // ���������� ������� � �������. ����� ��������� � ��� �� ����������
		//������� ������ ����		
		int shift_y = getYcoord(); //����������� ���������� �� Y ��� �������� ��������� �������
		for (auto it = elem->answers.begin(); it != elem->answers.end(); it++) //������� ������
		{
			if (it != elem->answers.begin()) setColor(0, 15);
			else setColor(0, 4);
			cout << "  " << it->text << endl;
		}
		int shift_key = getYcoord(); //����������� ���������� �� Y ��� �������� ��������� �������
		//������� ������� ������ � �����������
		GotoXY(3, shift_key + 3);
		cout << "S-->���������";
		GotoXY(20, shift_key + 3);
		cout << "N-->�����";
		// ���������� ������
		int m = 0;
		int pos = 0, last_pos = 0;// ���������� ��� ���������������� �������
		bool nex_step = false; // ���������� ��� ������� �����
		do
		{
			last_pos = pos;
			m = _getch();
			if (_kbhit()) m = _getch(); //������� ���� ��� ������ � ������ �.�. �������������� ������� ������ ������� ������
			switch (m)
			{
			case UP: pos--;
				break;
			case DOWN: pos++;
				break;
			case ENTER:
				elem->answers[pos].student_answer = !elem->answers[pos].student_answer; // ����������� �����
				//menu_copy[pos].second = !menu_copy[pos].second; //���������� ������
				GotoXY(1, pos + shift_y);
				//if (menu_copy[last_pos].second == true) cout << "+";
				if (elem->answers[pos].student_answer == true) cout << "+"; //������/������� ������� ������������ ������
				else cout << " ";
				break;
			}
			if (pos == size) pos = 0;
			else if (pos < 0) pos = size - 1;
			// ��������� ��������� �������
			GotoXY(2, last_pos + shift_y);
			setColor(0, 15);
			cout << elem->answers[last_pos].text;
			GotoXY(2, pos + shift_y);
			setColor(0, 4);
			cout << elem->answers[pos].text;
			if (m == 's' || m == 'S') //��������� �����
			{

				m = 'n'; // ����� �� �����
				exit = true;

			}

		} while (m != 'n' && m != 'N');

		if (exit == false)
		{
			//��������� �������
			compare_answers(*elem);
			num_question.pop_back(); // ����������� ������ �� ������
		}
		else
		{
			elem = test_question.end() - 1; //��������������� �����
			reverse(num_question.begin(), num_question.end()); //�������������� ������� ����� ����� �� �������
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
	file.write((char*)&size, sizeof(int)); // ����� ������ �������� ��������
	file.write((char*)exam.c_str(), size * sizeof(char)); // ����� �������� ��������
	size = way.size();
	file.write((char*)&size, sizeof(int)); // ����� ������ ���� �����
	file.write((char*)way.c_str(), size * sizeof(char)); // ����� ���� � �����
	file.write((char*)&correct_answer, sizeof(int)); // ���������� ������ �������
	file.write((char*)&incorrect_answer, sizeof(int)); // ���������� �� ������ �������
	size = num_question.size();
	file.write((char*)&size, sizeof(int)); //// ����� ������ ������� ������� ���������� �������� ��� �����
	for (auto it = num_question.begin(); it != num_question.end(); it++)
	{
		file.write((char*)&(*it), sizeof(int)); //����� ������ ���������� �������� ��� �����
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
		file.read((char*)&this->correct_answer, sizeof(int));//��������� ������ ������
		file.read((char*)&this->incorrect_answer, sizeof(int)); //��������� �������� ������
		file.read((char*)&temp, sizeof(int)); //������ ������ ������� � ����������� ���������
		int qw; //��������� ���������� ��� ���������� ������� ��������
		for (int i = 0; i < temp; i++)
		{
			file.read((char*)&qw, sizeof(int)); //������ ����� ����������� �������
			this->num_question.push_back(qw); // ��������� ��� � ������
		}
		/*file.close();
	}
	catch (const ifstream::failure& ex)
	{
		cout << "������ �������� �����" << endl;
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

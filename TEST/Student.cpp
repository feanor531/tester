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
	base.write((char*)&size, sizeof(int)); //���������� ���������� �������� � ������
	base.write((char*)this->login.c_str(), size * sizeof(char)); //���������� �����
	size = this->password.length();
	base.write((char*)&size, sizeof(int)); //���������� ���������� �������� � ������
	base.write((char*)this->password.c_str(), size * sizeof(char)); //���������� ������
	size = this->name.length();
	base.write((char*)&size, sizeof(int)); //���������� ���������� �������� � �����
	base.write((char*)this->name.c_str(), size * sizeof(char)); //���������� ���

	size = this->surname.length();
	base.write((char*)&size, sizeof(int)); //���������� ���������� �������� � �������
	base.write((char*)this->surname.c_str(), size * sizeof(char)); //���������� �������
	size = this->middle_name.length();
	base.write((char*)&size, sizeof(int)); //���������� ���������� �������� � ��������
	base.write((char*)this->middle_name.c_str(), size * sizeof(char)); //���������� ��������
	size = this->adress.length();
	base.write((char*)&size, sizeof(int)); //���������� ���������� �������� � �����
	base.write((char*)this->adress.c_str(), size * sizeof(char)); //���������� �����
	size = this->phohe_number.length();
	base.write((char*)&size, sizeof(int)); //���������� ���������� �������� � �������
	base.write((char*)this->phohe_number.c_str(), size * sizeof(char)); //���������� �������
	size = this->complete_exam.size();
	base.write((char*)&size, sizeof(int)); //���������� ���������� ��������� � �������
	
	for (auto& elem : complete_exam)
	{
		//pos = base.tellp();
		elem.writeExam(base); //����� ���������� ��������
		//pos = base.tellg();
	}
	size = this->incomplete_exam.size();
	base.write((char*)&size, sizeof(int)); //���������� ���������� ��������� � �������
	for (auto& elem : incomplete_exam)
	{
		//pos = base.tellp();
		elem.writeExam(base); //����� ������������ ��������
	}
}



int Student::saveToFile()
{
	int pos = this->pos_now;	
	int size, poss = 0;
	//int poss; // ������� � ����� ���� ������
	fstream base, tmp_base;
	base.exceptions(ifstream::badbit | ifstream::failbit);
	tmp_base.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		base.open("data_base.txt", ios::out | ios::binary | ios::in | ios::app | ios::ate); // ��� ate �� ����� �������� �������
		if (pos >= 0)
		{
			tmp_base.open("tmp_base.txt", ios::out | ios::binary | ios::trunc);
			base.seekp(0, ios::beg);
			while (base.tellp() != pos)
			{
				char ch;
				base.get(ch);
				tmp_base.put(ch);
				//base.read((char*)&c, sizeof(char)); //������ ��� �� �����
				//tmp_base.write((char*)c, sizeof(char)); // ���������� ���� ��� � �������� ����
			}
			write(tmp_base);// ������ ���������
			poss = tmp_base.tellp();
			poss = changeUsersPos(login, poss);
			saveToFileShortList();			
			//poss = base.tellp(); // ���������� ����� ��������� ������ ��������� ��������� 
			if (poss >= 0)
			{
				base.seekp(poss, ios::beg);
				while (base.peek() != EOF)
				{
					char ch;
					base.get(ch);
					tmp_base.put(ch);
					//base.read((char*)&c, sizeof(char)); //������ ��� �� �����
					//tmp_base.write((char*)c, sizeof(char)); // ���������� ���� ��� � �������� ����
				}
			}		
			
			base.close(); 
			tmp_base.close();
			remove("data_base.txt");
			if (rename("tmp_base.txt", "data_base.txt") != 0)
				cout << "Error!\n Couldn't rename file. �heck old and new filename...\n\n";
			//else
				//cout << "Ok...\n\n";
			//rename("temp.txt", "data_base.txt"); 

		}
		else
		{
			poss = base.tellp();
			write(base);// ������ ��������� � ����� �����
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
		cout << "������ �������� ����� data_base.txt" << endl;
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
		//base.read((char*)&temp, sizeof(int)); // ������ ������� ������� / �����
		base.read((char*)&temp, sizeof(int)); // ������ ������ ������
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // ������ �����
		str[temp] = '\0';
		this->login = str;
		base.read((char*)&temp, sizeof(int)); // ������ ������ ������
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // ������ ������
		str[temp] = '\0';
		this->password = str;
		base.read((char*)&temp, sizeof(int)); // ������ ������ ���
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // ������ ���
		str[temp] = '\0';
		this->name = str;
		base.read((char*)&temp, sizeof(int)); // ������ ������ �������
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // ������ �������
		str[temp] = '\0';
		this->surname = str;
		base.read((char*)&temp, sizeof(int)); // ������ ������ ��������
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // ������ ��������
		str[temp] = '\0';
		this->middle_name = str;
		base.read((char*)&temp, sizeof(int)); // ������ ������ �����
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // ������ �����
		str[temp] = '\0';
		this->adress = str;
		base.read((char*)&temp, sizeof(int)); // ������ ������ �������
		str = new char[temp + 1];
		base.read((char*)str, temp * sizeof(char)); // ������ �������
		str[temp] = '\0';
		this->phohe_number = str;
		base.read((char*)&temp, sizeof(int)); // ������ ������ ������ ���������� ���������
		for (int i = 0; i < temp; i++)
		{
			CompleteExam cmp;
			//poss = base.tellp();
			cmp.readExam(base); // ������ ������ ���������� ���������
			this->complete_exam.push_back(cmp);
		}
		base.read((char*)&temp, sizeof(int)); // ������ ������ ������ ������������ ���������
		for (int i = 0; i < temp; i++)
		{
			IncompleteExam inc;
			//poss = base.tellp();
			inc.readExam(base);
			this->incomplete_exam.push_back(inc); // ������ ������ ������������ ���������
		}
		base.close();
	}
	catch (const ifstream::failure& ex)
	{
		cout << "������ �������� ����� data_base.txt" << endl;
		cout << ex.what() << endl;
		ex.code();
		system("pause");
	}
}

void Student::StartExam(string name, string file)
{
	vector<question> q;
	IncompleteExam exam(name); //������� ������ �������������� ��������
	exam.SetWay(file); //���������� ����� ������������ �����
	auto it = find_if(incomplete_exam.begin(), incomplete_exam.end(), [&](IncompleteExam& exam) // ��������� ���� �� ���� � �������������
		{
			return exam.GetExamName() == name;
		});

	if (it == incomplete_exam.end())
	{
		exam.selectionQuestion(file); // ������������ � �������� ����������� ���������� ��������
		//q = exam.readQuestion(file); // ��������� �� ����� ����������� �������
	}
	
	else
	{
		exam = *it;
		incomplete_exam.erase(it);
	}
	
	
	
	q = exam.readQuestion(file); // ��������� �� ����� ����������� �������
	bool c = exam.startTest(q); //��������� ������������
	system("cls");
	if (c) // ���� �������� �� ��� �������
	{
		//������� ��������� ������ ������� ��������
		CompleteExam complete(exam.GetExamName(), exam.GetCorrectAnswer(), exam.GetIncorrectAnswer());
		this->complete_exam.push_back(complete); // ��������� � ������ �������� ���������
		//������� ���������� �� �������
		cout << setw(24) << "����: " << complete.GetExamName() << endl;
		cout << setw(24) << "������ �������: " << complete.GetCorrectAnswer() << endl;
		cout << setw(24) << "�������� �������: " << complete.GetIncorrectAnswer() << endl;
		cout << setw(24) << "������� ������ �������: " << complete.GetPersent() << endl;
		cout << setw(24) << "������: " << complete.GetGrade() << endl;
		cout << setw(24) << "���� ����� ��������: " << complete.GetDate(); //����
	}
	else
	{
		cout << "���� �� �������!" << endl;
		this->incomplete_exam.push_back(exam);

		
	}
	
	saveToFile(); //���������� �����
}




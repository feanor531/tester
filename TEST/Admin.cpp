#include "Admin.h"

int Admin::saveToFile()
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
			size = this->login.length();
			tmp_base.write((char*)&size, sizeof(int)); //���������� ���������� �������� � ������
			tmp_base.write((char*)this->login.c_str(), size * sizeof(char)); //���������� �����
			size = this->password.length();
			tmp_base.write((char*)&size, sizeof(int)); //���������� ���������� �������� � ������
			tmp_base.write((char*)this->password.c_str(), size * sizeof(char)); //���������� ������
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
			else
				cout << "Ok...\n\n";
			//rename("temp.txt", "data_base.txt"); 

		}
		else
		{
			//base.seekp(0, ios::end);
			poss = base.tellp();
			size = this->login.length();
			base.write((char*)&size, sizeof(int)); //���������� ���������� �������� � ������
			base.write((char*)this->login.c_str(), size * sizeof(char)); //���������� �����
			size = this->password.length();
			base.write((char*)&size, sizeof(int)); //���������� ���������� �������� � ������
			base.write((char*)this->password.c_str(), size * sizeof(char)); //���������� ������
			shotListUsers us;
			us.log = this->login;
			us.pass = this->password;
			us.pos_in_file = poss;
			us.is_admin = true;
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

void Admin::LoadData(int pos)
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
		base.close();
	}
	catch (const ifstream::failure& ex)
	{
		cout << "������ �������� ����� data_base.txt" << endl;
		cout << ex.what() << endl;
		ex.code();
	}
}
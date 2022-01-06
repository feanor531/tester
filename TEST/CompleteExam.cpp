#include "CompleteExam.h"

void CompleteExam::writeExam(fstream &file)
{
	int size;
	//fstream file;
	//file.exceptions(ifstream::badbit | ifstream::failbit);
	//try
	//{
	//	file.open("data_base.txt", ios::out | ios::binary);
	//	if (pos != -1) file.seekp(pos, ios::beg); // ���� �� ������� ������� �� ����� � �����
		size = exam.size();
		file.write((char*)&size, sizeof(int));// ����� ������ �������� ��������
		file.write((char*)&size, sizeof(int)); //����� ����� ����� ������ ��� ����, � �� ��������� 0
		file.write((char*)exam.c_str(), size * sizeof(char)); // ����� �������� ��������
		file.write((char*)&correct_answer, sizeof(int)); // ���������� ������ �������
		file.write((char*)&incorrect_answer, sizeof(int)); // ���������� �� ������ �������
		file.write((char*)&grade, sizeof(int));
		file.write((char*)&percent, sizeof(int));
		size = date.size();
		file.write((char*)&size, sizeof(int)); //
		file.write((char*)date.c_str(), size * sizeof(char)); // �����
	/*	pos = file.tellp();
		file.close();
		return pos;
	}
	catch (const ifstream::failure& ex)
	{
		cout << "������ �������� �����" << endl;
		cout << ex.what() << endl;
		ex.code();
	}*/
}

void CompleteExam::readExam(fstream &file)
{
	int temp;
	char* name, *date;
	/*fstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		file.open("data_base.txt", ios::in | ios::binary);
		file.seekg(pos, ios::beg);*/
		file.read((char*)&temp, sizeof(int));
		file.read((char*)&temp, sizeof(int)); //����� ����� ����� ������ ��� ����, � �� ��������� 0
		name = new char[temp + 1];
		file.read((char*)name, temp * sizeof(char));
		name[temp] = '\0';
		this->exam = name;
		delete[]name;
		file.read((char*)&correct_answer, sizeof(int));//��������� ������ ������
		file.read((char*)&incorrect_answer, sizeof(int)); //��������� �������� ������
		file.read((char*)&grade, sizeof(int)); // 
		file.read((char*)&percent, sizeof(int));
		file.read((char*)&temp, sizeof(int)); //�����
		date = new char[temp+1];
		file.read((char*)date, temp * sizeof(char));//�����
		date[temp] = '\0';
		this->date = date;
		delete[]date;

	/*	file.close();
	}
	catch (const ifstream::failure& ex)
	{
		cout << "������ �������� �����" << endl;
		cout << ex.what() << endl;
		ex.code();
	}*/
}



CompleteExam::CompleteExam(string exam, int correct_answer, int incorrect_answer) : Exams(exam, correct_answer, incorrect_answer)
{
	percent = ((double)correct_answer / ((double)(correct_answer + incorrect_answer))) * 100; // % ���������� ������� 
	if (percent <= 56) grade = 1;
	else grade = 12 - ((100 - percent) / 4); //������ ��� 12 ������� ������� (4-��� ���... 100%-12 ������, 96%-11 ������ ....)
	time_t sec = time(NULL);
	struct tm  local_time;
	localtime_s(&local_time, &sec);
	char buf[28];
	asctime_s(buf, &local_time);
	buf[27] = '\0';
	this->date = buf;
}


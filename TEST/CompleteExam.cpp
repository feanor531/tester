#include "CompleteExam.h"

void CompleteExam::writeExam(fstream &file)
{
	int size;
	//fstream file;
	//file.exceptions(ifstream::badbit | ifstream::failbit);
	//try
	//{
	//	file.open("data_base.txt", ios::out | ios::binary);
	//	if (pos != -1) file.seekp(pos, ios::beg); // если не извесна позиция то пишем в конец
		size = exam.size();
		file.write((char*)&size, sizeof(int));// пишем размер названия экзамена
		file.write((char*)&size, sizeof(int)); //вынос мозга нужно писать два раза, а то считывает 0
		file.write((char*)exam.c_str(), size * sizeof(char)); // пишем названия экзамена
		file.write((char*)&correct_answer, sizeof(int)); // количество верных ответов
		file.write((char*)&incorrect_answer, sizeof(int)); // количество не верных ответов
		file.write((char*)&grade, sizeof(int));
		file.write((char*)&percent, sizeof(int));
		size = date.size();
		file.write((char*)&size, sizeof(int)); //
		file.write((char*)date.c_str(), size * sizeof(char)); // время
	/*	pos = file.tellp();
		file.close();
		return pos;
	}
	catch (const ifstream::failure& ex)
	{
		cout << "Ошибка открытия файла" << endl;
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
		file.read((char*)&temp, sizeof(int)); //вынос мозга нужно писать два раза, а то считывает 0
		name = new char[temp + 1];
		file.read((char*)name, temp * sizeof(char));
		name[temp] = '\0';
		this->exam = name;
		delete[]name;
		file.read((char*)&correct_answer, sizeof(int));//считываем верные ответы
		file.read((char*)&incorrect_answer, sizeof(int)); //считываем неверные ответы
		file.read((char*)&grade, sizeof(int)); // 
		file.read((char*)&percent, sizeof(int));
		file.read((char*)&temp, sizeof(int)); //время
		date = new char[temp+1];
		file.read((char*)date, temp * sizeof(char));//время
		date[temp] = '\0';
		this->date = date;
		delete[]date;

	/*	file.close();
	}
	catch (const ifstream::failure& ex)
	{
		cout << "Ошибка открытия файла" << endl;
		cout << ex.what() << endl;
		ex.code();
	}*/
}



CompleteExam::CompleteExam(string exam, int correct_answer, int incorrect_answer) : Exams(exam, correct_answer, incorrect_answer)
{
	percent = ((double)correct_answer / ((double)(correct_answer + incorrect_answer))) * 100; // % правильных ответов 
	if (percent <= 56) grade = 1;
	else grade = 12 - ((100 - percent) / 4); //расчет для 12 бальной системы (4-это шаг... 100%-12 баллов, 96%-11 баллов ....)
	time_t sec = time(NULL);
	struct tm  local_time;
	localtime_s(&local_time, &sec);
	char buf[28];
	asctime_s(buf, &local_time);
	buf[27] = '\0';
	this->date = buf;
}


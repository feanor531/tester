#pragma once
#ifndef _CompleteExam_H
#define _CompleteExam_H

#include"Exams.h"
#include<time.h>
//#include<string>
//#include<iostream>
//#include<fstream>
class CompleteExam :
	public Exams
{
protected:
	int grade = 0; // ������
	int percent = 0; // % ���������� ������� 
	string date; //���� ����� ��������
	//void setGrade()
	//{
	//	percent = (correct_answer / (correct_answer + incorrect_answer)) * 100; // % ���������� ������� 
	//	grade = 12 - ((100 - percent) / 4); //������ ��� 12 ������� ������� (4-��� ���... 100%-12 ������, 96%-11 ������ ....)
	//}
public:
	int GetGrade() { return grade; }
	int GetPersent() { return percent; }
	string GetDate() { return date; }
	virtual void writeExam(fstream& file);
	virtual void readExam(fstream& file);
	CompleteExam(string exam = " ", int correct_answer = 0, int incorrect_answer = 0);
	~CompleteExam() {}
};

#endif // !_CompleteExam_H






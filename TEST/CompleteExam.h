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
	int grade = 0; // оценка
	int percent = 0; // % правильных ответов 
	string date; //дата сдачи экзамена
	//void setGrade()
	//{
	//	percent = (correct_answer / (correct_answer + incorrect_answer)) * 100; // % правильных ответов 
	//	grade = 12 - ((100 - percent) / 4); //расчет для 12 бальной системы (4-это шаг... 100%-12 баллов, 96%-11 баллов ....)
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






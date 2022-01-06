#pragma once
#ifndef _EXAMS_H
#define _EXAMS_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<Windows.h>
#include<conio.h>
using namespace std;

class Exams
{
protected:
	string exam; // название экзамена	
	int correct_answer; // количество верных ответов
	int incorrect_answer; // количество не верных ответов


public:
	string GetExamName() { return exam; }
	int GetCorrectAnswer() { return correct_answer; }
	int GetIncorrectAnswer() { return incorrect_answer; }
	virtual void writeExam(fstream& file) = 0;
	virtual void readExam(fstream& file) = 0;

	Exams(string exam = " ", int correct_answer = 0, int incorrect_answer = 0) : exam{ exam }, correct_answer{ correct_answer }, incorrect_answer{ incorrect_answer } {}
	//~Exams(){}
};
#endif // !_EXAMS_H

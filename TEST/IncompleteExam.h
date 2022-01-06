#pragma once
#ifndef _IncompleteExam_H
#define _IncompleteExam_H
#include "Exams.h"
//#include"Header.h"


struct answer
{
	string text = "answer"; // текст ответа
	bool true_answer = false; // правильный ответ или нет
	bool student_answer = false; // ответ студента
};

struct question
{
	string question_ = "qwestion"; // текст вопроса 
	vector<answer> answers; //список ответов с признаком верно/неверно
};

class addNumberFrom
{
	int delta;
	int current;
public:
	addNumberFrom(int number, int from = 0) :delta(number), current(from) {}
	int operator()()
	{
		return current += delta;
	}
};





class IncompleteExam :
	public Exams
{
private:

	enum KEY
	{
		UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13
	};

	int getXcoord();
	int getYcoord();
	void GotoXY(int X, int Y);
	void setColor(int Background, int Text);
	void compare_answers(question& qwestion); // парсинг правильных ответов
protected:
	vector<int> num_question; //номера оставшихся вопросов для теста
	string way;
public:
	void selectionQuestion(string qwestion_file);
	vector<question> readQuestion(string qwestion_file);
	bool startTest(vector<question>&);
	vector<int> GetNumQwestion() { return num_question; }
	string GetWay() { return way; }
	void SetWay(string _way) { way = _way; }
	virtual void writeExam(fstream &file);
	virtual void readExam(fstream& file);
	IncompleteExam(string _exam = " ", int _correct_answer = 0, int _incorrect_answer = 0) : Exams(_exam, _correct_answer, _incorrect_answer) {}
	//IncompleteExam(IncompleteExam &ex);
	~IncompleteExam() {}
	IncompleteExam& operator=(const IncompleteExam& right);
};

#endif // !_IncompleteExam_H






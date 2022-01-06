#pragma once
#include<iostream>
#include <time.h>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<map>
#include<algorithm>
#include<Windows.h>
#include <conio.h>
#include "User.h"
#include "Student.h"
#include "Admin.h"
#include "Menu.h"
#include "Exams.h"
#include "CompleteExam.h"
#include"IncompleteExam.h"
using namespace std;


enum MENU
{
	AUTHORIZATION, REGISTRATION, EXIT, BACK,// ������� ����
	CHANGE_PASS, USER_MANAGEMENT, VIEW_STATISTIC, TEST_MANAGEMENT, NEXT,// ������� ���� ������	
	ADD_USER, DEL_USER, CHANGE_USER, // ������� ������ USER_MANAGEMENT
	STATISTIC_CATEGORY, STATISTIC_TEST, STATISTIC_USER, // ������� ������ VIEW_STATISTIC
	ADD_CATEGORY, DEL_CATEGORY, ADD_TEST, DEL_TEST, CHANGE_TESTS, // ������� ������ TEST_MANAGEMENT
	HISTORY, UNFINISHED_EXAMS, PASS_EXAM// ������� ���� ��������
};
enum KEY
{
	UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13
};


int getXcoord();
int getYcoord();

//template <typename T>
//auto MENU(T menu); // ������� ����
void GotoXY(int X, int Y); // ������� �� �������� �������
void setColor(int Background, int Text); // ��������� ����� ������
void registration();
void autorization();
void adminMenu(int pos_in_file);
void studentMenu(int pos_in_file);
void passExam(Student &);
void unfinishedExam(Student& stud);
void history(Student& stud);
void changePassAdmin(Admin& adm);




#pragma once
#ifndef _User_H
#define _User_H
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;


struct shotListUsers
{
	string log;
	string pass;
	int pos_in_file;
	bool is_admin;
};



class User
{
	
protected:
	string login;
	string password;
	int pos_now = -1;
	static vector<shotListUsers> users;
	
public:
	User(string login = "Admin", string password = "Admin");
	string GetLogin() { return login; }
	string GetPassword() { return password; }
	void posNow(int d) { pos_now = d; }
	static vector<shotListUsers> GetshortListUsers() { return users; }
	void SetLogin(string login);
	void SetPassword(string password);
	virtual int saveToFile() = 0;
	virtual void LoadData(int pos) = 0;
	
	static void encryption(string& word); //кодировка логина - пароля
	void decryption(string& word); //декодировка логина - пароля
	static int welcome(string &login, string &password);
	static void LoadShortList();
	void saveToFileShortList();
	int changeUsersPos(string login, int end_pos);
	void saveUserPosInFile(shotListUsers&);
};



#endif // !_User_H
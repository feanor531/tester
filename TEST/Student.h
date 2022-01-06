#pragma once
#include "User.h"
//#include "Main.h"
#include "CompleteExam.h"
#include "IncompleteExam.h"
#include <iomanip>
#include<vector>
#include<map>


class Student :
    public User
{
protected:
    string name;
    string surname;
    string middle_name;
    string adress;
    string phohe_number;
    vector<CompleteExam> complete_exam; //история сдачи экзаменов
    vector<IncompleteExam> incomplete_exam; //не завершенные экзамены
    void write(fstream &base);
public:
    Student() {};
    Student(string _name, string _surname, string _middle_name, string _adress, string _phohe_number, string _login, string _password);
   // ~Student();
    void SetName(string name) { this->name = name; }
    void SetSurname(string surname) { this->surname = surname; }
    void SetMiddle_name(string middle_name) { this->middle_name = middle_name; }
    void SetAdress(string adress) { this->adress = adress; }
    void SetPhohe_number(string phohe_number) { this->phohe_number = phohe_number; }
    string GetName() { return name; }
    string GetSurname() { return surname; }
    string GetMiddle_name() { return middle_name; }
    string GetAdress() { return adress; }
    string GetPhohe_number() { return phohe_number; }
    vector<CompleteExam> GetCompleteExam() { return complete_exam; }
    vector<IncompleteExam> GetIncompleteExam() { return incomplete_exam; }
    virtual int saveToFile();
    virtual void LoadData(int pos);
    void StartExam(string name, string file);

    
};


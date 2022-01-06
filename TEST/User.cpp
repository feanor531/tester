#include "User.h"

User::User(string _login, string _password)
{
	login = _login;
	password = _password;
}


vector<shotListUsers> User::users;

void User::SetLogin(string login)
{
	encryption(login);

	for (auto& elem : users)
	{
		if (elem.log == this->login)
		{		
			elem.log = login;
			break;
		}
	}
	this->login = login;
}
void User::SetPassword(string password)
{
	encryption(password);
	for (auto& elem : users)
	{
		if (elem.pass == this->password)
		{
			elem.pass = password;
			break;
		}
	}
	this->password = password;
}

void User::encryption(string& word)
{
	int shift = word.size() % 247;
	for (auto& elem : word)
	{
		elem += shift + 100;
	}
}

void User::decryption(string& word)
{
	int shift = word.size() % 247;
	for (auto& elem : word)
	{
		elem -= shift + 100;
	}
}




int User::welcome(string &login, string &password)
{
	encryption(login);
	encryption(password);
	auto result = find_if(users.begin(), users.end(), [&](const shotListUsers &us) // находим в списке нашего юзера
		{
			return us.log == login;
		});
	if (result == users.end()) { return -2; } // если такого нет возвращаем -2
	else
	{
		if (result->pass != password) return -1; // а если только пароль  не совпадает возвращаем -1
		else return result->pos_in_file; //ну а если все совпало -во звращаем позицию в файле
	}
	
}

int User::changeUsersPos(string login, int end_pos) //корректировка позиций списка расположений всех юзеров
{
	sort(users.begin(), users.end(), [](const shotListUsers& us1, const shotListUsers& us2) // сортируем для уверенности
		{
			return us1.pos_in_file < us2.pos_in_file;
		});
	auto result = find_if(users.begin(), users.end(), [&](const shotListUsers& us) // находим в списке нашего юзера
		{
			return us.pos_in_file > pos_now;
		});
	///int now = pos_now;

	//auto result = upper_bound(users.begin(), users.end(), [&](const shotListUsers& us) // находим в списке нашего юзера
	//	{
	//		return us.pos_in_file > pos_now;
	//	});
	if (result != users.end())
	{
		int pos_next = result->pos_in_file; // находим позицию начала записи следующего по списку юзера
		int shift_pos = end_pos - pos_next; // находим позицию смещения
		vector<shotListUsers>::iterator it;
		for (it = result; it != users.end(); it++)
		{
			it->pos_in_file += shift_pos; // смещаем оставшиеся позиции
		}
		return pos_next;
	}
	return -1;
}

void User::saveUserPosInFile(shotListUsers &elem)
{
	int size;
	fstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		file.open("users.txt", ios::out | ios::binary | ios::app);
		{
			size = elem.log.length();
			file.write((char*)&size, sizeof(int)); //lengh login
			file.write((char*)elem.log.c_str(), size * sizeof(char)); //login
			size = elem.pass.length();
			file.write((char*)&size, sizeof(int)); //lengh pass
			file.write((char*)elem.pass.c_str(), size * sizeof(char)); //pass
			file.write((char*)&elem.pos_in_file, sizeof(int)); //pos_in_file pass		
			file.write((char*)&elem.is_admin, sizeof(char)); //
		}
		file.close();
	}
	catch (const ifstream::failure& ex)
	{
		cout << "Ошибка открытия файла" << endl;
		cout << ex.what() << endl;
		ex.code();
	}
}

void User::LoadShortList()
{
	fstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		file.open("users.txt", ios::in | ios::binary);
		char* str;
		bool a;
		int temp;
		if (file.is_open())
		{
			while (file.peek() > 0)//file.read((char*)&temp, sizeof(int)))
			{
				shotListUsers us;
				file.read((char*)&temp, sizeof(int));
				str = new char[temp + 1];
				file.read((char*)str, temp * sizeof(char));
				str[temp] = '\0';
				us.log = str;
				delete[]str;
				file.read((char*)&temp, sizeof(int));
				str = new char[temp + 1];
				file.read((char*)str, temp * sizeof(char));
				str[temp] = '\0';
				us.pass = str;
				file.read((char*)&temp, sizeof(int));
				us.pos_in_file = temp;
				file.read((char*)&a, sizeof(char));
				us.is_admin = a;
				users.push_back(us);
			}
		}
		//vector<shot_list_users> tmp;
		
		file.close();
	}
	catch (const ifstream::failure& ex)
	{
		cout << "Ошибка открытия файла" << endl;
		cout << ex.what() << endl;
		ex.code();
	}
}

void User::saveToFileShortList()
{
	int size;
	fstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		file.open("users.txt", ios::out | ios::binary | ios::trunc);
		for (auto& elem : users)
		{
			size = elem.log.length();
			file.write((char*)&size, sizeof(int)); //lengh login
			file.write((char*)elem.log.c_str(), size * sizeof(char)); //login
			size = elem.pass.length();
			file.write((char*)&size, sizeof(int)); //lengh pass
			file.write((char*)elem.pass.c_str(), size * sizeof(char)); //pass
			file.write((char*)&elem.pos_in_file, sizeof(int)); //pos_in_file pass		
			file.write((char*)&elem.is_admin, sizeof(char)); //
		}
		file.close();
	}
	catch (const ifstream::failure& ex)
	{
		cout << "Ошибка открытия файла" << endl;
		cout << ex.what() << endl;
		ex.code();
	}
}
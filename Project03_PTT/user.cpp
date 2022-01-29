#include "user.h"
//int user::ID_amount = 0;
user::user()
{
	account = '\0'; password = '\0'; postsID.clear(); Permission_level = 0;
}
user::user(int level)
{
	account = '\0'; password = '\0'; postsID.clear(); Permission_level = level;
}
user::user(string account)
{
	ifstream file;
	string temp;
	int tempN;
	file.open("./User/" + account + ".txt");
	file >> this->Permission_level;
	getline(file, temp);
	file >> this->account;
	getline(file, temp);
	file >> this->password;
	getline(file, temp);
	while (file >> tempN)
	{
		this->postsID.push_back(tempN);
		getline(file, temp);
	}
	file.close();
}
//void user::setIDManager(int id)
//{
//	ID_amount = id;
//}
void user::setAccount(string account)
{
	this->account = account;
}
void user::setPassword(string password)
{
	this->password = password;
}
bool user::isPasswordCorret(string temp)
{
	return this->password == temp ? true : false;
}
void user::addPost(int id)
{
	this->postsID.push_back(id);
	this->update();
}
void user::deletePost(int id)
{
	if (user::Authority(id))
	{
		postsID.erase(find(postsID.begin(), postsID.end(), id));
		this->update();
	}
}
bool user::Authority(int id)
{
	return find(postsID.begin(), postsID.end(), id) != postsID.end() ? true : false;
}
string user::getAccount()
{
	return this->account;
}
void user::save()
{
	ofstream fileU("./User/" + this->account + ".txt");
	fileU << this->Permission_level << endl;
	fileU << this->account << endl;
	fileU << this->password << endl;
	fileU.close();
}
void user::update()
{
	ofstream fileU("./User/" + this->account + ".txt");
	fileU << this->Permission_level << endl;
	fileU << this->account << endl;
	fileU << this->password << endl;
	for (int i = 0; i < postsID.size(); i++)
	{
		fileU << postsID[i] << endl;
	}
	fileU.close();
}





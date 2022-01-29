#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class user
{
	//int ID;
	//static int ID_amount;
protected:
	string account;
	string password;
	vector<int>postsID;
	int Permission_level;
public:
	user();
	user(int);
	user(string);
	/*static void addAccountManager(string);
	static void setIDManager(int);*/
	virtual void setAccount(string);
	virtual void setPassword(string);
	bool isPasswordCorret(string);
	virtual void addPost(int);
	virtual void deletePost(int);
	virtual bool Authority(int);
	/*virtual int myID();*/
	virtual string memberType() = 0;
	string getAccount();
	void save();
	void update();
};

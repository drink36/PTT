#pragma once

#include "user.h"

class Guest :public user
{
	string Type = "Guest";
public:
	Guest();
	virtual bool Authority(int id);
	virtual string memberType();
};

class Member :public user
{
	string Type = "Member";
public:
	Member();
	Member(string);
	virtual bool Authority(int id);
	virtual string memberType();
};

class Administrator :public user
{
	string Type = "Administrator";
public:
	Administrator();
	Administrator(string);
	Administrator(Member);
	virtual bool Authority(int id);
	virtual string memberType();
};
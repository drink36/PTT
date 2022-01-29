#include "userObjects.h"

Guest::Guest() :user(0) {}
bool Guest::Authority(int id) { return false; }
string Guest::memberType() { return this->Type; }

Member::Member() : user(1) {}
Member::Member(string account) : user(account) {}
bool Member::Authority(int id) { return user::Authority(id); }
string Member::memberType() { return this->Type; }

Administrator::Administrator() : user(2) {}
Administrator::Administrator(string account) : user(account) {}
Administrator::Administrator(Member temp)
{
	*this = temp;
	this->Permission_level = 2;
	user::update();
}
bool Administrator::Authority(int id) { return true; }
string Administrator::memberType() { return this->Type; }

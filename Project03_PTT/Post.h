#pragma once
#include "userObjects.h"
struct comment
{
	string like = "\0";
	string name = "\0";
	string messege = "\0";
};
class Post
{
	int ID;
	string dir;
	string Writer;
	string Title;
	string Text;
	vector<comment> comments;

public:
	Post();
	Post(string, int);
	Post(string, string);
	void setWriter(string);
	void setTitle(string);
	void setText(string);
	void setComment(string,string, string);
	void deleteComment(int num);
	void changeComment(int, string);
	void savePost();
	void changePost(Post);
	string getWriter(void);
	string getTitle(void);
	string getText(void);
	int getId(void);
	bool alreadyLike(string);
	bool alreadyDisLike(string);
	vector <comment> getComment();

};
#pragma once
#include "Board.h"
using namespace std;

class viewer
{
	string upper;
	string command_up;
	vector<string> text;
	vector <comment> comments;
	int commentS;
	int comment_row;
	int row;
	int	textS;
	int start;
	int end;
public:
	viewer();
	void setUpper(string);
	void setText(vector<Board>,string type);
	void setText(Board,bool flag);
	void setText(Post,string,bool flag);
	void setRow(int);
	void setCommentRow(int);
	void show();
	void showTweet();
	void showComment();
	void showPostText(Post);
	void showLoginA(bool);
	void showLoginB(bool);
	void showReA(bool);
	void showReB(bool);
	void showCreateBoard(bool);
	void showCreatePostA();
	void showCreatePostb(Post);
	void showCheckAgain();
	void showChangePost(Post);
	void showAddComment(string);
	void showDeleteMessege();
};
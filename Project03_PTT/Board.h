#pragma once
#include "Post.h"
#include <cstdio>
#include <direct.h>
class Board
{
	string name;
	vector<Post> Posts;
	vector<string> PostManager;
public:
	Board();
	Board(string);
	string getName(void);
	void setName(string);
	void save(void);
	void Softupdate(void);
	void Hardupdate(void);
	void deleteBoard(void);
	void deletePost(int);
	void addPost(int, Post);
	void changePost(int, Post);
	void setComment(string, string, string, int);
	void deleteComment(int, int);
	void deleteComment(int, int, string);
	vector<Post> getPosts();
	int Postsize();
};


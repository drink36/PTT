#include "Post.h"
Post::Post()
{
	this->ID = 1;
}
Post::Post(string dir, int id)
{
	this->ID = id;
	this->dir = dir;
	comments.clear();
}
Post::Post(string dir, string name)
{
	this->dir = dir;
	char stop = 19;
	ifstream file;
	file.open("./Board/" + dir + "/" + name + ".txt");
	this->Title = name;
	file >> this->ID;
	file >> this->Writer;
	string temp;
	getline(file, temp);
	getline(file, this->Text, stop);
	comment t;
	stop = 19;
	while (file >> t.like)
	{
		file >> t.name;
		getline(file, t.messege, stop);
		comments.push_back(t);
	}
}
void Post::savePost()
{
	char stop = 19;
	ofstream file;
	file.open("./Board/" + dir + "/" + this->Title + ".txt");
	file << this->ID << endl;
	file << this->Writer << endl;
	file << this->Text + stop << endl;
	for (int i = 0; i < this->comments.size(); i++)
		file << this->comments[i].like << " " << this->comments[i].name << " " << this->comments[i].messege + stop << endl;
	file.close();
}
void Post::changePost(Post post)
{
	*this = post;
	this->savePost();
}
void Post::setWriter(string writer)
{
	this->Writer = writer;
}
void Post::setTitle(string title)
{
	this->Title = title;
}
void Post::setText(string text)
{
	this->Text = text;
}
void Post::setComment(string type,string name, string messege)
{
	comment temp;
	temp.like = type;
	temp.name = name;
	temp.messege = messege;
	comments.push_back(temp);
	this->savePost();
}
void Post::deleteComment(int num)
{
	comments.erase(comments.begin() + num);
	this->savePost();
}
void Post::changeComment(int num, string messege)
{
	comments[num].like = "normal";
	comments[num].name = "delete because";
	comments[num].messege = messege;
	this->savePost();
}
string Post::getWriter()
{
	return this->Writer;
}
string Post::getTitle()
{
	return this->Title;
}
string Post::getText()
{
	return this->Text;
}
int Post::getId(void)
{
	return this->ID;
}
bool Post::alreadyLike(string name)
{
	for (int i = 0; i < comments.size(); i++)
	{
		if (comments[i].like == "like" && comments[i].name == name)
			return true;
	}
	return false;
}
bool Post::alreadyDisLike(string name)
{
	for (int i = 0; i < comments.size(); i++)
	{
		if (comments[i].like == "dislike" && comments[i].name == name)
			return true;
	}
	return false;
}
vector <comment> Post::getComment()
{
	return this->comments;
}
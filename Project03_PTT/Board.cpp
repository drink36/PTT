#include "Board.h"
Board::Board()
{
	this->name = '\0';
	PostManager.clear();
	Posts.clear();
}
Board::Board(string name)
{
	this->name = name;
	fstream file;
	string temp;
	file.open("./Board/" + this->name + "/Menu.txt");
	while (getline(file, temp))
		PostManager.push_back(temp);
	file.close();
	for (int i = 0; i < PostManager.size(); i++)
	{
		Posts.push_back(Post(this->name, PostManager[i]));
	}
}
string Board::getName(void)
{
	return this->name;
}
void Board::setName(string name)
{
	this->name = name;
}
void Board::save(void)
{
	string folderPath = "./Board/" + this->name;

	_mkdir(folderPath.c_str());
	ofstream file("./Board/" + this->name + "/Menu.txt");
	file.close();
}
void Board::Softupdate(void)
{
	Posts.clear();
	PostManager.clear();
	fstream file;
	string temp;
	file.open("./Board/" + this->name + "/Menu.txt");
	while (getline(file, temp))
		PostManager.push_back(temp);
	file.close();
	for (int i = 0; i < PostManager.size(); i++)
	{
		Posts.push_back(Post(this->name, PostManager[i]));
	}
}
void Board::Hardupdate(void)
{
	ofstream file;
	file.open("./Board/" + this->name + "/Menu.txt");
	for (int i = 0; i < PostManager.size(); i++)
	{
		file << PostManager[i] << endl;
	}
}
void Board::deleteBoard(void)
{

	string name = "./Board/" + this->name;
	string menu = name + "/Menu.txt";
	remove(menu.c_str());
	_rmdir(name.c_str());
}
void Board::deletePost(int num)
{
	string name = PostManager[num];
	PostManager.erase(PostManager.begin() + num);
	name = "./Board/" + this->name + "/" + name + ".txt";
	remove(name.c_str());
	this->Hardupdate();
	this->Softupdate();
}
void Board::addPost(int id, Post post)
{
	Post temp(this->name, id);
	temp.setWriter(post.getWriter());
	temp.setTitle(post.getTitle());
	temp.setText(post.getText());
	temp.savePost();
	this->Posts.push_back(temp);
	this->PostManager.push_back(temp.getTitle());
	this->Hardupdate();
}
void Board::changePost(int num, Post post)
{
	this->Posts[num].changePost(post);
}
void Board::setComment(string type,string name, string messege, int num)
{
	this->Posts[num].setComment(type,name, messege);
}
void Board::deleteComment(int num, int row)
{
	this->Posts[num].deleteComment(row);
}
void Board::deleteComment(int num, int row, string messege)
{
	this->Posts[num].changeComment(row, messege);
}
vector<Post> Board::getPosts()
{
	return this->Posts;
}
int Board::Postsize()
{
	return this->PostManager.size();
}
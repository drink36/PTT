#include "viewer.h"
viewer::viewer()
{
	this->upper = "=============================================================================================\n";
	this->upper += "=     =========      ===========      ===========                                           =\n";
	this->upper += "=     =       =           =                =                                                =\n";
	this->upper += "=     =========           =                =                                                =\n";
	this->upper += "=     =                   =                =                                                =\n";
	this->upper += "=     =                   =                =                                                =\n";
	this->upper += "=     =                   =                =                                                =\n";
	this->upper += "=============================================================================================\n";
	this->text.clear();
	this->row = 0;
}
void viewer::setUpper(string upper)
{
	this->upper = upper;
}
void viewer::setText(vector <Board> text,string type)
{
	this->command_up = "\0";
	if (type == "Administrator")
	{
		this->command_up += "=   (->)entry board  (esc)sign out (¡ô,¡õ)select board (c)create new board  (d)delete board =\n";
	}
	else
	{
		this->command_up += "=   (->)entry board  (esc)sign out (¡ô,¡õ)select board                                      =\n";
	}
	this->command_up += "=============================================================================================\n";
	this->text.clear();
	for (int i = 0; i < text.size(); i++)
		this->text.push_back(text[i].getName());
	this->textS = text.size();
	this->start = 0;
	this->end = textS > 19 ? 19 : textS;
}
void viewer::setText(Board temp,bool flag)
{
	this->command_up = "\0";
	if (flag)
	{
		this->command_up += "=   (->)entry post  (<-)back to board  (¡ô,¡õ)select post  (c)create new post (d)delete post=\n";
	}
	else
	{
		this->command_up += "=   (->)entry post  (<-)back to board  (¡ô,¡õ)select post  (c)create new post               =\n";
	}
	this->command_up += "=============================================================================================\n";
	vector<Post>text = temp.getPosts();
	this->text.clear();
	for (int i = 0; i < text.size(); i++)
		this->text.push_back(text[i].getTitle());
	this->textS = text.size();
	this->start = 0;
	this->end = textS > 19 ? 19 : textS;
}
void viewer::setText(Post post, string type, bool flag)
{
	this->command_up = "\0";
	if (type == "Administrator")
	{
		this->command_up += "=   (s)comment  (<-)back to select post (¡ô,¡õ)select comment (c)edit post (d)delete comment=\n";
	}
	else if (flag)
	{
		this->command_up += "=   (s)comment  (<-)back to select post (¡ô,¡õ)select comment (c)edit post                  =\n";
	}
	else
	{
		this->command_up += "=   (s)comment  (<-)back to select post (¡ô,¡õ)select comment                               =\n";
	}
	this->command_up += "=============================================================================================\n";
	this->comments = post.getComment();
	this->commentS = comments.size();
	this->start = 0;
	this->end = commentS;
}
void viewer::showPostText(Post post)
{
	system("cls");
	cout << this->upper;
	cout << this->command_up;
	cout << "Writer : " << post.getWriter() << "\n";
	cout << post.getTitle() << "\n\n";
	cout << "=============================================================================================\n";
	cout << post.getText() << endl;
	cout << "=============================================================================================\n";
}
void viewer::setRow(int row)
{
	this->row = row;
	this->start = (row / 19) * 19;
	this->end = this->start + 19 > textS ? textS : this->start + 19;
}
void viewer::setCommentRow(int row)
{
	this->comment_row = row;
	this->start = (row / 19) * 19;
	this->end = this->start + 19 > commentS ? commentS : this->start + 19;
}
void viewer::show()
{
	system("cls");
	cout << this->upper;
	cout << this->command_up;
	for (int i = start; i < end; i++)
	{
		if (i != row)
		{
			cout << "   " << this->text[i] << endl;
		}
		else
		{
			cout << "-->" << this->text[i] << endl;
		}
	}
}
void viewer::showTweet()
{
	this->command_up= "=    (l)like  (d)dislike  (s)just comment (esc)cancel comment                                =\n";
	this->command_up += "=============================================================================================\n";
}
void viewer::showComment()
{
	for (int i = start; i < end; i++)
	{
		if (i != comment_row)
			cout << "   ";
		else
			cout << "-->";
		if (comments[i].like == "normal")
			cout << "   ";
		else if (comments[i].like == "like")
			cout << "±À ";
		else if (comments[i].like == "dislike")
			cout << "¼N ";
		cout << this->comments[i].name << " " << this->comments[i].messege << endl;
	}
}
void viewer::showLoginA(bool flag)
{
	system("cls");
	cout << this->upper;
	this->command_up  = "=  (new)create new account  (guest)use guest to login  (enter account)use account to login  =\n";
	this->command_up += "=============================================================================================\n";
	cout << this->command_up;
	if (flag)
		cout << "No such account";
	cout << '\n';
	cout << "Please Enter Account\n";
}
void viewer::showLoginB(bool flag)
{
	system("cls");
	cout << this->upper;
	this->command_up = "=  Please entry password                                                                    =\n";
	this->command_up += "=============================================================================================\n";
	cout << this->command_up;
	if (flag)
		cout << "Incorret Password\n";
}
void viewer::showReA(bool flag)
{
	system("cls");
	cout << this->upper;
	this->command_up = "=  Please entry the account you want                                                        =\n";
	this->command_up += "=============================================================================================\n";
	cout << this->command_up;
	if (flag)
		cout << "Account exist\n";
}
void viewer::showReB(bool flag)
{
	system("cls");
	cout << this->upper;
	this->command_up = "=  Please entry the password you want                                                       =\n";
	this->command_up += "=============================================================================================\n";
	cout << this->command_up;
	if (flag)
		cout << "Illegal Password\n";
}
void viewer::showCreateBoard(bool flag)
{
	system("cls");
	cout << this->upper;
	this->command_up = "=  Please entry the Board you want                                                          =\n";
	this->command_up += "=============================================================================================\n";
	cout << this->command_up;
	if (flag)
		cout << "Board exsit\n";
}
void viewer::showCreatePostA(void)
{
	system("cls");
	cout << this->upper;
	this->command_up = "=  Please entry the Title name you want                                                     =\n";
	this->command_up += "=============================================================================================\n";
	cout << this->command_up;
}
void viewer::showCreatePostb(Post temp)
{
	system("cls");
	cout << this->upper;
	this->command_up = "=  Please entry the text you want (^s)finish text                                           =\n";
	this->command_up += "=============================================================================================\n";
	cout << this->command_up;
	cout << "Writer : " << temp.getWriter() << "\n";
	cout << temp.getTitle() << "\n\n";
	cout << "=============================================================================================\n";
}
void viewer::showCheckAgain()
{
	system("cls");
	cout << this->upper;
	cout << "Are you sure (y/n)?\n";
}
void viewer::showChangePost(Post post)
{
	system("cls");
	cout << this->upper;
	cout << this->command_up;
	cout << "Writer : " << post.getWriter() << "\n";
	cout << post.getTitle() << "\n";
	cout << "If you want to change the text, please copy and paste it to the blank text for change\n";
	cout << "=============================================================================================\n";
	cout << post.getText() << endl;
	cout << "=============================================================================================\n";
}
void viewer::showAddComment(string name)
{
	cout << "If you want to quit or finish, Please entry ^s\n";
	cout << "   " << name << " ";
}
void viewer::showDeleteMessege()
{
	cout << "This is for you to leave an error message, if you want to quit or finish,Please entry ^s\n";
}
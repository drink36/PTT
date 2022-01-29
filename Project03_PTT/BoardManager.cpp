#include "BoardManager.h"
BoardManager::BoardManager()
{
	string temp;
	fstream fileS;
	fileS.open("./User/Manager.txt");
	while (getline(fileS, temp))
	{
		Admin.push_back(temp);
	}
	fileS.close();
	fileS.open("./User/Menu.txt");
	while (getline(fileS, temp))
	{
		accountManager.push_back(temp);
		if (find(Admin.begin(), Admin.end(), temp) != Admin.end())
			users.push_back(new Administrator(temp));
		else
			users.push_back(new Member(temp));
	}
	fileS.close();
}
void BoardManager::start()
{
	fstream fileB;
	fileB.open("./Board/Menu.txt");
	string tempN;
	fileB >> this->posts;
	getline(fileB, tempN);
	while (getline(fileB, tempN))
	{
		boards.push_back(Board(tempN));
		boardsManager.push_back(tempN);
	}
	menu();
}
bool BoardManager::Login()
{
	string account;
	string password;
	bool flag = false;
	do
	{
		Viewer.showLoginA(flag);
		cin >> account;
		flag = 1;
	} while (find(accountManager.begin(), accountManager.end(), account) == accountManager.end() && account != "new" && account != "guest");
	if (account == "new")
		return registered();
	else if (account == "guest")
	{
		main_user = new Guest;
		return true;
	}
	else
	{
		main_user = users[this->findAccount(account)];
		bool flag = false;
		do
		{
			Viewer.showLoginB(flag);
			cin >> password;
			flag = 1;
		} while (!main_user->isPasswordCorret(password));
		return true;
	}
}
bool BoardManager::registered()
{
	string account;
	string password;
	bool flag = false;
	do
	{
		Viewer.showReA(flag);
		cin >> account;
		flag = 1;
	} while (find(accountManager.begin(), accountManager.end(), account) != accountManager.end());
	member.setAccount(account);
	flag = 0;
	Viewer.showReB(flag);
	cin >> password;
	member.setPassword(password);
	member.save();
	users.push_back(&member);
	accountManager.push_back(member.getAccount());
	this->main_user = users[findAccount(member.getAccount())];
	
	ofstream file;
	file.open("./User/Menu.txt");
	for (int i = 0; i < accountManager.size(); i++)
	{
		file << accountManager[i] << endl;
	}
	file.close();
	cout << main_user->getAccount() << '\n';
	return true;
}
int BoardManager::findAccount(string account)
{
	for (int i = 0; i < accountManager.size(); i++)
		if (accountManager[i] == account)
			return i;
}
void BoardManager::menu()
{
	while (Login())
		select_board();
}
void BoardManager::select_board()
{
	int row = 0;
	while (1)
	{
		Viewer.setText(boards,this->main_user->memberType());
		Viewer.setRow(row);
		Viewer.show();
		switch (_getch())
		{
		case Arrow::Scan:
		{
			switch (_getch())
			{
			case Arrow::Right:
			{
				board(row);
				break;
			}
			case Arrow::Left:
			{
				break;
			}
			case Arrow::Up:
			{
				row = row > 0 ? row - 1 : 0;
				break;
			}
			case Arrow::Down:
			{
				row = row < boards.size() - 1 ? row + 1 : boards.size() - 1;

				break;
			}
			}
			break;
		}
		case 99:
		{
			if (main_user->memberType() == "Administrator")
				this->createBoard();
			break;
		}
		case 100:
		{
			if (main_user->memberType() == "Administrator")
				this->deleteBoard(row);
			break;
		}
		case 27:
		{
			return;
		}
		default:
			break;
		}
	}
}
void BoardManager::board(int num)
{
	int row = 0;
	while (1)
	{
		if (boards[num].Postsize() != 0)
			Viewer.setText(boards[num], main_user->Authority(boards[num].getPosts()[row].getId()));
		else
			Viewer.setText(boards[num], 0);
		Viewer.setRow(row);
		Viewer.show();
		switch (_getch())
		{
		case Arrow::Scan:
		{
			switch (_getch())
			{
			case Arrow::Right:
			{
				if (boards[num].Postsize() != 0)
					post(num, row);
				break;
			}
			case Arrow::Left:
			{
				return;
				break;
			}
			case Arrow::Up:
			{
				row = row > 0 ? row - 1 : 0;
				break;
			}
			case Arrow::Down:
			{
				row = row < boards[num].Postsize() - 1 ? row + 1 : boards[num].Postsize() - 1;
				break;
			}
			}
			break;
		}
		case 99:
		{
			if (main_user->memberType() != "Guest")
				this->createPost(num);
			break;
		}
		case 100:
		{
			if (main_user->Authority(boards[num].getPosts()[row].getId()))
				this->deletePost(num, row);
			break;
		}
		default:
			break;
		}
	}
}
void BoardManager::post(int numb, int num)
{
	int row = 0;
	while (1)
	{
		Viewer.setText(boards[numb].getPosts()[num], main_user->memberType(), main_user->Authority(boards[numb].getPosts()[num].getId()));
		Viewer.setCommentRow(row);
		if (main_user->Authority(boards[numb].getPosts()[num].getId()))
			Viewer.showChangePost(boards[numb].getPosts()[num]);
		else
			Viewer.showPostText(boards[numb].getPosts()[num]);
		Viewer.showComment();
		switch (_getch())
		{
		case Arrow::Scan:
		{
			switch (_getch())
			{
			case Arrow::Left:
			{
				return;
				break;
			}
			case Arrow::Up:
			{
				row = row > 0 ? row - 1 : 0;
				break;
			}
			case Arrow::Down:
			{
				row = row < boards[numb].getPosts()[num].getComment().size() - 1 ? row + 1 : boards[numb].getPosts()[num].getComment().size() - 1;
				break;
			}
			}
			break;
		}
		case 99:
		{
			if (main_user->Authority(boards[numb].getPosts()[num].getId()))
				this->changePost(numb, num);
			break;
		}
		case 100:
		{
			if (main_user->memberType() == "Administrator" && boards[numb].getPosts()[num].getComment().size() != 0)
				this->deleteComment(numb, num, row);
			break;
		}
		case 115:
		{
			if (main_user->memberType() != "Guest")
			{
				this->tweet(numb,num);
			}
			break;
		}
		default:
			break;
		}
	}
}
void BoardManager::tweet(int num,int row)
{
	Viewer.showTweet();
	if (main_user->Authority(boards[num].getPosts()[row].getId()))
		Viewer.showChangePost(boards[num].getPosts()[row]);
	else
		Viewer.showPostText(boards[num].getPosts()[row]);
	Viewer.showComment();
	char temp;
	string type;
	while (1)
	{
		temp = _getch();
		if (temp == 'l')
		{
			if (boards[num].getPosts()[row].alreadyLike(main_user->getAccount()))
			{
				cout << "You already like it.\n";
				continue;
			}
			else
			{
				type = "like";
				break;
			}
		}
		else if (temp == 'd')
		{
			if (boards[num].getPosts()[row].alreadyDisLike(main_user->getAccount()))
			{
				cout << "You already dislike it.\n";
				continue;
			}
			else
			{
				type = "dislike";
				break;
			}
		}
		else if (temp == 's')
		{
			type = "normal";
			break;
		}
		else if (temp == 27)
		{
			return;
		}
	}
	this->speak(type,num, row);
}
void BoardManager::createBoard()
{
	string name;
	Board temp;
	bool flag = 0;
	cin.ignore();
	do
	{
		Viewer.showCreateBoard(flag);
		getline(cin, name);
		flag = 1;
	} while (find(boardsManager.begin(), boardsManager.end(), name) != boardsManager.end());
	temp.setName(name);
	temp.save();
	boards.push_back(temp);
	boardsManager.push_back(name);
	this->MenuUpdate();
}
void BoardManager::createPost(int num)
{
	Post temp;
	temp.setWriter(main_user->getAccount());
	string name;
	char stop = 19;
	Viewer.showCreatePostA();
	getline(cin, name);
	getline(cin, name);
	temp.setTitle(name);
	Viewer.showCreatePostb(temp);
	getline(cin, name, stop);
	temp.setText(name);
	boards[num].addPost(this->posts, temp);
	main_user->addPost(this->posts);
	this->posts++;
	this->MenuUpdate();
}
void BoardManager::deleteBoard(int num)
{
	char temp;
	do
	{
		Viewer.showCheckAgain();
		temp = _getch();
	} while (temp != 'y' && temp != 'n');
	if (temp == 'n')
		return;
	else
	{
		while (boards[num].Postsize() != 0)
			this->deletePostwithBoard(num, 0);
		boards[num].deleteBoard();
		boards.erase(boards.begin() + num);
		boardsManager.erase(boardsManager.begin() + num);
		this->MenuUpdate();
	}
}
void BoardManager::deletePostwithBoard(int num, int row)
{
	char temp;
	do
	{
		Viewer.showCheckAgain();
		temp = _getch();
	} while (temp != 'y' && temp != 'n');
	if (temp == 'n')
		return;
	else
	{
		for (int i = 0; i < users.size(); i++)
		{
			users[i]->deletePost(boards[num].getPosts()[row].getId());
		}
		boards[num].deletePost(row);
	}
}
void BoardManager::deletePost(int num, int row)
{
	char temp;
	do
	{
		Viewer.showCheckAgain();
		temp = _getch();
	} while (temp != 'y' && temp != 'n');
	if (temp == 'n')
		return;
	else
	{
		for (int i = 0; i < users.size(); i++)
		{
			users[i]->deletePost(boards[num].getPosts()[row].getId());
		}
		if (main_user->memberType() == "Administrator")
			deletePostByAdmin(num, row);
		else
			boards[num].deletePost(row);
	}
}
void BoardManager::deletePostByAdmin(int num, int row)
{
	Post temp = boards[num].getPosts()[row];
	Viewer.showDeleteMessege();
	string messege;
	char stop = 19;
	cin.ignore();
	getline(cin, messege, stop);
	if (messege.size() == 0)
	{
		boards[num].deletePost(row);
		return;
	}
	messege = "Delete because:\n"+messege;
	temp.setText(messege);
	boards[num].changePost(row, temp);
}
void BoardManager::changePost(int num, int row)
{
	Post temp = boards[num].getPosts()[row];
	string title = temp.getTitle();
	string text;
	char stop = 19;
	Viewer.showCreatePostb(temp);
	cin.ignore();
	getline(cin, text, stop);
	temp.setText(text);
	boards[num].changePost(row, temp);
}
void BoardManager::MenuUpdate()
{
	ofstream fileB;
	fileB.open("./Board/Menu.txt");
	fileB << this->posts << endl;
	for (int i = 0; i < boardsManager.size(); i++)
		fileB << boardsManager[i] << endl;
	fileB.close();
	fstream fileS;
	fileS.open("./Board/Menu.txt");
	string tempN;
	fileS >> this->posts;
	getline(fileS, tempN);
	boards.clear();
	boardsManager.clear();
	while (getline(fileS, tempN))
	{
		boards.push_back(Board(tempN));
		boardsManager.push_back(tempN);
	}
}
void BoardManager::speak(string type,int num, int row)
{
	Viewer.showAddComment(main_user->getAccount());
	cin.ignore();
	string messege = "\0";
	char stop = 19;
	getline(cin, messege, stop);
	if (messege.size() == 0)
		return;
	else
	{
		boards[num].setComment(type,main_user->getAccount(), messege, row);
	}
}
void BoardManager::deleteComment(int boards_num, int post_num, int comment_num)
{
	Viewer.showDeleteMessege();
	string messege;
	char stop = 19;
	cin.ignore();
	getline(cin, messege, stop);
	if (messege.size() == 0)
	{
		boards[boards_num].deleteComment(post_num, comment_num);
	}
	else
	{
		boards[boards_num].deleteComment(post_num, comment_num, messege);
	}
}
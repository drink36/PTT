#pragma once
#include "viewer.h"
#include <conio.h>
enum BoardState
{
    MENU,
    SELECT_BOARD,
    BOARD,
    POST
};
enum Arrow
{
    Scan = 224,
    Up = 72,
    Down = 80,
    Left = 75,
    Right = 77
};
class BoardManager
{
    vector <user*> users;
    user* main_user;
    vector <Board> boards;
    Member member;
    vector <string> boardsManager;
    vector<string> accountManager;
    vector<string> Admin;
    int current_user;
    int posts;
    string username;
    viewer Viewer;

public:
    BoardManager();
    void start();
    bool Login();
    bool registered();
    int findAccount(string);
    void menu();
    void select_board();
    void board(int);
    void post(int, int);
    void tweet(int, int);
    void createBoard();
    void createPost(int);
    void deleteBoard(int);
    void deletePost(int, int);
    void deletePostwithBoard(int, int);
    void deletePostByAdmin(int, int);
    void changePost(int, int);
    void speak(string,int, int);
    void deleteComment(int, int, int);
    void MenuUpdate();
};
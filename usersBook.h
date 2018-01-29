#ifndef USERSBOOK_H
#define USERSBOOK_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include "user.h"
#include "Markup.h"


using namespace std;

class UsersBook
{
    int numberOfUsers;

public:
    UsersBook();
    int getNumberOfUsers();
    int signIn(vector<User> &users);
    void signUp(vector<User> &users);
    void changePassword(vector<User> &users, int idOfTheLoggedUser);

private:
    void createAFileIfItdoesNotExist(string fileName);
    int convertStringToInt(string number);
    void setNumberOfUsers(int numberOfUsers);
    void loadUsersFromFile(vector<User> &users);
    void addUserToFile(vector<User> &users, User newUser);
};

#endif

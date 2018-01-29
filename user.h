#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User
{
    int userId;
    string login;
    string password;
    string name;
    string surname;

public:
    User(int userId, string login, string password, string name, string surname);
    int getUserId();
    void setUserId(int userId);
    string getLogin();
    void setLogin(string login);
    string getPassword();
    void setPassword(string password);
    string getName();
    void setName(string name);
    string getSurname();
    void setSurname(string surname);
};

#endif

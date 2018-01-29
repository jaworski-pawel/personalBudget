#include <iostream>
#include "user.h"

using namespace std;

User::User(int userId, string login, string password, string name, string surname)
{
    this -> userId = userId;
    this -> login = login;
    this -> password = password;
    this -> name = name;
    this -> surname = surname;
}

int User::getUserId()
{
    return userId;
}

void User::setUserId(int userId)
{
    this -> userId = userId;
}

string User::getLogin()
{
    return login;
}

void User::setLogin(string login)
{
    this -> login = login;
}

string User::getPassword()
{
    return password;
}

void User::setPassword(string password)
{
    this -> password = password;
}

string User::getName()
{
    return name;
}

void User::setName(string name)
{
    this -> name = name;
}

string User::getSurname()
{
    return surname;
}

void User::setSurname(string surname)
{
    this -> surname = surname;
}

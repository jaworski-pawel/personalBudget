#include <iostream>
#include "usersBook.h"

using namespace std;

UsersBook::UsersBook()
{
    numberOfUsers = 0;
}

int UsersBook::getNumberOfUsers()
{
    return numberOfUsers;
}

int UsersBook::signIn(vector<User> &users)
{
    string login, password;
    loadUsersFromFile(users);

    cout << "Enter the login: ";
    cin >> login;
    int i = 0;
    while (i < numberOfUsers)
    {
        if (users[i].getLogin() == login)
        {
            for (int attempt = 0; attempt < 3; attempt++)
            {
                cout << "Enter the password: ";
                cin >> password;
                if (users[i].getPassword() == password)
                {
                    cout << "You signed in." << endl;
                    Sleep(1000);
                    return users[i].getUserId();
                }
            }
            cout << "You entered the wrong password 3 times. Wait 5 seconds..." << endl;
            Sleep(5000);
            return 0;
        }
        i++;
    }
    cout << "There is no such user." << endl;
    Sleep(3000);
    return 0;
}

void UsersBook::signUp(vector<User> &users)
{
    string login, password, name, surname;
    loadUsersFromFile(users);

    cout << "Enter the login: ";
    cin >> login;
    int i = 0;

    while (i < numberOfUsers)
    {
        if (users[i].getLogin() == login)
        {
            cout << "Such a user exists. Enter another login: ";
            cin >> login;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Enter the password: ";
    cin >> password;
    cout << "Enter the name: ";
    cin >> name;
    cout << "Enter the surname: ";
    cin >> surname;
    numberOfUsers++;
    User temporaryUser(numberOfUsers, login, password, name, surname);
    users.push_back(temporaryUser);
    cout << "You signed up" << endl;
    Sleep(1000);
    addUserToFile(users, temporaryUser);
}

void UsersBook::changePassword(vector<User> &users, int idOfTheLoggedUser)
{
    string newPassword;
    cout << "Enter a new password: ";
    cin >> newPassword;

    CMarkup xml;

    createAFileIfItdoesNotExist("users.xml");
    xml.Load("users.xml");

    xml.FindElem();
    xml.IntoElem();

    while (xml.FindElem("user"))
    {
        xml.IntoElem();
        xml.FindElem( "userId" );
        if (idOfTheLoggedUser == convertStringToInt(xml.GetData()))
        {
            xml.FindElem( "password" );
            xml.SetData( newPassword );
            xml.Save("users.xml");
            cout << "Password changed." << endl;
            Sleep(1000);
            break;
        }
        xml.OutOfElem();
    }
}

void UsersBook::loadUsersFromFile(vector<User> &users)
{
    numberOfUsers = 0;

    users.erase(users.begin(), users.end());

    CMarkup xml;

    createAFileIfItdoesNotExist("users.xml");
    xml.Load("users.xml");

    string userId, login, password, name, surname;

    xml.FindElem();
    xml.IntoElem();

    while ( xml.FindElem("user") )
    {
        xml.IntoElem();
        xml.FindElem( "userId" );
        userId = xml.GetData();
        xml.FindElem( "login" );
        login = xml.GetData();
        xml.FindElem( "password" );
        password = xml.GetData();
        xml.FindElem( "name" );
        name = xml.GetData();
        xml.FindElem( "surname" );
        surname = xml.GetData();
        xml.OutOfElem();
        numberOfUsers++;
        User temporaryUser(convertStringToInt(userId), login, password, name, surname);
        users.push_back(temporaryUser);
    }
}

void UsersBook::createAFileIfItdoesNotExist(string fileName)
{
    fstream file;
    file.open(fileName.c_str(), ios::in);
    if ( file.is_open() )
    {
        file.close();
    }
    else
    {
        file.close();
        file.open(fileName.c_str(), ios::out);
        file.close();
    }

}

int UsersBook::convertStringToInt(string number)
{
    int integerNumber = atoi(number.c_str());
    return integerNumber;
}

void UsersBook::setNumberOfUsers(int numberOfUsers)
{
    this -> numberOfUsers = numberOfUsers;
}

void UsersBook::addUserToFile(vector<User> &users, User newUser)
{
    CMarkup xml;

    createAFileIfItdoesNotExist("users.xml");
    xml.Load("users.xml");

    if(!xml.FindElem("users"))
    {
        xml.SetDoc( "<?xml version=\"1.0\" encoding=\"UTF\"?>\r\n" );
        xml.AddElem( "users" );
    }
    xml.IntoElem();
    xml.AddElem( "user" );
    xml.IntoElem();
    xml.AddElem( "userId", newUser.getUserId() );
    xml.AddElem( "login",  newUser.getLogin() );
    xml.AddElem( "password", newUser.getPassword() );
    xml.AddElem( "name", newUser.getName() );
    xml.AddElem( "surname", newUser.getSurname() );
    xml.Save("users.xml");
}

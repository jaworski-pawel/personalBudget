#include <iostream>
#include <windows.h>
#include <vector>
#include "budget.h"
#include "expense.h"
#include "income.h"
#include "user.h"
#include "usersBook.h"

using namespace std;

int main()
{
    vector<User> users;
    UsersBook usersBook;
    Budget budget;
    char selection;

    while (true)
    {
        if (budget.getIdOfTheLoggedUser() == 0)
        {
            system("cls");
            cout << "Personal budget - main menu." << endl << endl;
            cout << "1. Sign up" << endl;
            cout << "2. Sign in" << endl;
            cout << "9. Exit" << endl << endl;
            cout << "Selection: ";
            cin >> selection;

            switch (selection)
            {
            case '1':
                {
                    usersBook.signUp(users);
                    break;
                }
            case '2' :
                {
                    budget.setIdOfTheLoggedUser(usersBook.signIn(users));
                    break;
                }
            case '9':
                {
                    exit(0);
                    break;
                }
            }
        }
    }

    return 0;
}

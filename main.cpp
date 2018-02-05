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
            cout << "Personal budget - main menu" << endl << endl;
            cout << "1. Sign up" << endl;
            cout << "2. Sign in" << endl;
            cout << "3. Exit" << endl << endl;
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
            case '3':
                {
                    exit(0);
                    break;
                }
            }
        }
        else
        {
            system("cls");
            cout << "Personal budget - user menu" << endl << endl;
            cout << "1. Add income" << endl;
            cout << "2. Add expense" << endl;
            cout << "3. Show balance from the current month" << endl;
            cout << "4. Show balance from the previous month" << endl;
            cout << "5. Show balance from the selected period" << endl;
            cout << "6. Change password" << endl;
            cout << "7. Sign out" << endl << endl;
            cin >> selection;

            switch (selection)
            {
            case '1':
                {
                    budget.addIncome();
                    break;
                }
            case '2':
                {
                    budget.addExpense();
                    break;
                }
            case '3':
                {
                    budget.showBalanceFromTheCurrentMonth();
                    break;
                }
            case '4':
                {
                    budget.showBalanceFromThePreviousMonth();
                    break;
                }
            case '5':
                {
                    budget.showBalanceFromTheSelectedPeriod();
                    break;
                }
            case '6':
                {
                    usersBook.changePassword(users, budget.getIdOfTheLoggedUser());
                    break;
                }
            case '7':
                {
                    budget.setIdOfTheLoggedUser(0);
                    break;
                }
            }
        }
    }

    return 0;
}

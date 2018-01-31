#include <iostream>
#include <windows.h>
#include "budget.h"

using namespace std;

Budget::Budget()
{
    idOfTheLoggedUser = 0;
}

int Budget::getIdOfTheLoggedUser()
{
    return idOfTheLoggedUser;
}

void Budget::setIdOfTheLoggedUser(int idOfTheLoggedUser)
{
    this -> idOfTheLoggedUser = idOfTheLoggedUser;
}

int Budget::getNumberOfIncomes()
{
    return numberOfIncomes;
}

void Budget::setNumberOfIncomes(int numberOfIncomes)
{
    this -> numberOfIncomes = numberOfIncomes;
}

int Budget::getNumberOfExpenses()
{
    return numberOfExpenses;
}

void Budget::setNumberOfExpenses(int numberOfExpenses)
{
    this -> numberOfExpenses = numberOfExpenses;
}

void Budget::addIncome()
{
    char selection;

    system("cls");
    cout << "Adding a income" << endl << endl;
    cout << "1. Current date" << endl;
    cout << "2. Another date" << endl << endl;
    cin >> selection;

    switch (selection)
    {
    case '1':
    {
        int incomeId, userId, date;
        string item;
        float amount;

        incomeId = assignOperationId("incomes.xml");
        userId = idOfTheLoggedUser;
        date = getCurrentTime();
        system("cls");
        cout << "Adding a income with current date" << endl << endl;
        cout << "Enter the item: ";
        cin >> item;
        cout << "Enter the amount: ";
        cin >> amount;

        CMarkup xml;

        createAFileIfItdoesNotExist("incomes.xml");
        xml.Load("incomes.xml");
        if(!xml.FindElem("incomes"))
        {
            xml.SetDoc( "<?xml version=\"1.0\" encoding=\"UTF\"?>\r\n" );
            xml.AddElem( "incomes" );
        }
        xml.IntoElem();
        xml.AddElem( "income" );
        xml.IntoElem();
        xml.AddElem( "incomeId", incomeId );
        xml.AddElem( "userId", userId );
        xml.AddElem( "date", date );
        xml.AddElem( "amount", amount);
        xml.Save("incomes.xml");

        cout << "Income added" << endl;
        Sleep(1000);

        break;
    }
    case '2':
    {
        //ustaw date
        break;
    }
    }
}

void Budget::addExpense()
{
    int expenseId, userId, date;
    string item;
    float amount;

    system("cls");
    cout << "Adding an expense" << endl;
    cout << "Enter expense ID";
    cin >> expenseId;
    cout << "Enter the date: ";
    cin >> date;
    cout << "Enter the item: ";
    cin >> item;
    cout << "Enter the amount";
    cin >> amount;

    CMarkup xml;

    createAFileIfItdoesNotExist("expenses.xml");
    xml.Load("expenses.xml");
    if(!xml.FindElem("expenses"))
    {
        xml.SetDoc( "<?xml version=\"1.0\" encoding=\"UTF\"?>\r\n" );
        xml.AddElem( "expenses" );
    }
    xml.IntoElem();
    xml.AddElem( "expenseId", expenseId);
    xml.AddElem( "userId", idOfTheLoggedUser );
    xml.AddElem( "date", date );
    xml.AddElem( "amount", amount);
    xml.Save("expenses.xml");
}

void Budget::createAFileIfItdoesNotExist(string fileName)
{
    fstream file;
    file.open(fileName.c_str(), ios::in);
    if ( file.is_open() )
    {
        file.close();
        cout << "File is exist";
    }
    else
    {
        file.close();
        cout << "File is not exist" << endl;
        file.open(fileName.c_str(), ios::out);
        file.close();
    }

}

int Budget::getCurrentTime()
{
    time_t currentTime;
    time(&currentTime);
    return currentTime;
}

int Budget::assignOperationId(string fileName)
{
    int newId = 1;
    CMarkup xml;

    createAFileIfItdoesNotExist(fileName);
    xml.Load(fileName);
    xml.FindElem();
    xml.IntoElem();
    while ( xml.FindElem("income") )
    {
        newId++;
    }
    return newId;
}

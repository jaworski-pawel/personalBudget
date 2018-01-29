#include <iostream>
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
    int incomeId, userId, date;
    string item;
    float amount;

    system("cls");
    cout << "Adding a income" << endl;
    cout << "Enter incomeid";
    cin >> incomeId;
    cout << "Enter the date: ";
    cin >> date;
    cout << "Enter the item: ";
    cin >> item;
    cout << "Enter the amount";
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
    xml.AddElem( "incomeId", incomeId);
    xml.AddElem( "userId" , idOfTheLoggedUser );
    xml.AddElem( "date" , date );
    xml.AddElem( "amount", amount);
    xml.Save("incomes.xml");
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

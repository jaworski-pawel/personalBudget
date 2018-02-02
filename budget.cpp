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
        addIncomeToFile(getCurrentTime());
        break;
    }
    case '2':
    {
        string anotherDate;
        bool repeat = true;

        while (repeat)
        {
            cout << "Enter the date(yyyy-mm-dd): ";
            cin >> anotherDate;
            repeat = !checkData(anotherDate);
        }
        addIncomeToFile(convertDateToInt(anotherDate));
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
    }
    else
    {
        file.close();
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

void Budget::addIncomeToFile(int date)
{
    int incomeId, userId;
    string item;
    float amount;

    incomeId = assignOperationId("incomes.xml");
    userId = idOfTheLoggedUser;
    system("cls");
    cout << "Adding a income" << endl << endl;
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
}

int Budget::convertStringToInt(string number)
{
    int integerNumber = atoi(number.c_str());
    return integerNumber;
}

bool Budget::checkData(string date)
{
    int year, month, day;
    time_t currentTime;
    time(&currentTime);
    struct tm * today;
    today = localtime(& currentTime);
    int currentYear = today -> tm_year + 1900;
    int currentMonth = today -> tm_mon + 1;

    if (date.length() == 10)
    {
        year = convertStringToInt(date.substr(0, 4));
        month = convertStringToInt(date.substr(5, 2));
        day = convertStringToInt(date.substr(8, 2));
    }
    else
    {
        cout << "Incorrect date. Please enter the date in format yyyy-mm-dd since January 01, 2000 to today." << endl;
        Sleep(3000);
        return false;
    }

    if (year >=2000 && year <= currentYear && month >= 1 && day >=1 && day <= getTheNumberOfDaysOfTheMonth(year, month))
    {
        if (year == currentYear)
        {
            if (month <= currentMonth)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        cout << "Incorrect date. Please enter the date in format yyyy-mm-dd since January 01, 2000 to today." << endl;
        Sleep(3000);
        return false;
    }
}

int Budget::convertDateToInt(string date)
{
    int year, month, day;
    struct tm timeToConvert;

    if (date.length() == 10)
    {
        year = convertStringToInt(date.substr(0, 4));
        month = convertStringToInt(date.substr(5, 2));
        day = convertStringToInt(date.substr(8, 2));
    }
    else
    {
        cout << "Incorrect date. Please enter the date in format yyyy-mm-dd since January 01, 2000 to today." << endl;
        Sleep(3000);
        return -1;
    }

    timeToConvert.tm_year = year - 1900;
    timeToConvert.tm_mon = month - 1;
    timeToConvert.tm_mday = day;
    timeToConvert.tm_hour = 0;
    timeToConvert.tm_min = 0;
    timeToConvert.tm_sec = 1;
    timeToConvert.tm_isdst = -1;

    return mktime(&timeToConvert);
}

int Budget::getTheNumberOfDaysOfTheMonth(int year, int month)
{
    if (month%2 == 1)
    {
        return 31;
    }
    else
    {
        if (month%2 == 0 && month != 2)
        {
            return 30;
        }
        else
        {
            if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
            {
                return 29;
            }
            else
            {
                return 28;
            }
        }
    }
}

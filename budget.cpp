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
    char selection;

    system("cls");
    cout << "Adding a expense" << endl << endl;
    cout << "1. Current date" << endl;
    cout << "2. Another date" << endl << endl;
    cin >> selection;

    switch (selection)
    {
    case '1':
    {
        addExpenseToFile(getCurrentTime());
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
        addExpenseToFile(convertDateToInt(anotherDate));
        break;
    }
    }
}

void Budget::showBalanceFromTheCurrentMonth()
{
    int startingDate, endDate;
    time_t currentTime;
    time(&currentTime);
    struct tm * today;
    today = localtime(& currentTime);
    int currentYear = today -> tm_year + 1900;
    int currentMonth = today -> tm_mon + 1;

    today -> tm_mday = 1;
    startingDate = mktime(today);

    today -> tm_mday = getTheNumberOfDaysOfTheMonth(currentYear, currentMonth);
    endDate = mktime(today);

    cout << "Balance from the current month" << endl << endl;

    showBalance(startingDate, endDate);
}

void Budget::showBalanceFromThePreviousMonth()
{
    int startingDate, endDate;
    time_t currentTime;
    time(&currentTime);
    struct tm * today;
    today = localtime(& currentTime);
    today -> tm_mon--;
    int previousMonth = today -> tm_mon + 1;
    if (previousMonth == 0)
    {
        previousMonth = 12;
        today -> tm_mon = 11;
        today -> tm_year--;
    }
    int currentYear = today -> tm_year + 1900;

    today -> tm_mday = 1;
    startingDate = mktime(today);

    today -> tm_mday = getTheNumberOfDaysOfTheMonth(currentYear, previousMonth);
    endDate = mktime(today);

    cout << "Balance from the previous month" << endl << endl;

    showBalance(startingDate, endDate);
}

void Budget::showBalance(int startingDate, int endDate)
{
    double sumOfIncomes, sumOfExpenses, balance;
    vector<Operation> incomes;
    vector<Operation> expenses;
    loadDataFromFile(incomes, startingDate, endDate, "income");
    sortingOperationsByDate(incomes);
    cout << "Incomes:" << endl;
    sumOfIncomes = showOperations(incomes);
    loadDataFromFile(expenses, startingDate, endDate, "expense");
    sortingOperationsByDate(expenses);
    cout << "Expenses:" << endl;
    sumOfExpenses = showOperations(expenses);
    cout << endl << "Sum of incomes: " << sumOfIncomes << endl;
    cout << "Sum of expenses: " << sumOfExpenses << endl << endl;
    cout << "Balance: " << sumOfIncomes - sumOfExpenses << endl << endl;
    system("pause");
}

void Budget::loadDataFromFile(vector<Operation> &operations, int startingDate, int endDate, string typeOfOperation)
{
    string fileName = typeOfOperation + "s.xml";
    string nameOfOperationId = typeOfOperation + "Id";

    operations.erase(operations.begin(), operations.end());

    CMarkup xml;

    createAFileIfItdoesNotExist(fileName);
    xml.Load(fileName);

    string operationId, userId, date, item, amount;

    xml.FindElem();
    xml.IntoElem();

    while (xml.FindElem(typeOfOperation))
    {
        xml.IntoElem();
        xml.FindElem(nameOfOperationId);
        operationId = xml.GetData();
        xml.FindElem("userId");
        userId = xml.GetData();
        xml.FindElem("date");
        date = xml.GetData();
        xml.FindElem("item");
        item = xml.GetData();
        xml.FindElem("amount");
        amount = xml.GetData();
        xml.OutOfElem();
        Operation temporaryOperation(convertStringToInt(operationId), convertStringToInt(userId), convertStringToInt(date), item, convertStringToDouble(amount));
        if(temporaryOperation.getUserId() == idOfTheLoggedUser && temporaryOperation.getDate() > startingDate && temporaryOperation.getDate() < endDate)
        {
            operations.push_back(temporaryOperation);
        }
    }
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
    string item, amount;

    incomeId = assignOperationId("incomes.xml");
    userId = idOfTheLoggedUser;
    system("cls");
    cout << "Adding a income" << endl << endl;
    cout << "Enter the item: ";
    cin >> item;
    cout << "Enter the amount: ";
    cin >> amount;
    if (amount.find_first_of(',') != string::npos)
    {
        amount[amount.find_first_of(',')] = '.';
    }

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
    xml.AddElem( "item", item);
    xml.AddElem( "amount", amount);
    xml.Save("incomes.xml");

    cout << "Income added" << endl;
    Sleep(1000);
}

void Budget::addExpenseToFile(int date)
{
    int expenseId, userId;
    string item, amount;

    expenseId = assignOperationId("expenses.xml");
    userId = idOfTheLoggedUser;
    system("cls");
    cout << "Adding a expense" << endl << endl;
    cout << "Enter the item: ";
    cin >> item;
    cout << "Enter the amount: ";
    cin >> amount;
    if (amount.find_first_of(',') != string::npos)
    {
        amount[amount.find_first_of(',')] = '.';
    }

    CMarkup xml;

    createAFileIfItdoesNotExist("expenses.xml");
    xml.Load("expenses.xml");
    if(!xml.FindElem("expenses"))
    {
        xml.SetDoc( "<?xml version=\"1.0\" encoding=\"UTF\"?>\r\n" );
        xml.AddElem( "expenses" );
    }
    xml.IntoElem();
    xml.AddElem( "expense" );
    xml.IntoElem();
    xml.AddElem( "expenseId", expenseId );
    xml.AddElem( "userId", userId );
    xml.AddElem( "date", date );
    xml.AddElem( "item", item);
    xml.AddElem( "amount", amount);
    xml.Save("expenses.xml");

    cout << "Expense added" << endl;
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

double Budget::convertStringToDouble(string number)
{
    double floatNumber = atof(number.c_str());
    return floatNumber;
}

void Budget::sortingOperationsByDate(vector<Operation> &operations)
{
    int numberOfOperations = operations.size();
    for (int i = 1; i < numberOfOperations; i++)
    {
        for (int j = numberOfOperations - 1; j >= 1; j--)
        {
            if (operations[j].getDate() < operations[j-1].getDate())
            {
                swap(operations[j], operations[j-1]);
            }
        }
    }
}

double Budget::showOperations(vector<Operation> &operations)
{
    int numberOfOperations = operations.size();
    double sumOfOperations = 0;

    for (int i = 0; i < numberOfOperations; ++i)
    {
        cout << "Operation ID: " << operations[i].getOperationId() << " Date: " << showDate(operations[i].getDate()) << " Item: " << operations[i].getItem() << " Amount: " << operations[i].getAmount() << endl;
        sumOfOperations += operations[i].getAmount();
    }
    return sumOfOperations;
}

string Budget::showDate(int time)
{
    char bufor[11];
    time_t timeToConversion = time;
    struct tm * dateToShow;
    dateToShow = localtime(&timeToConversion);
    strftime(bufor, 11, "%Y-%m-%d", dateToShow);
    return bufor;
}

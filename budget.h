#ifndef BUDGET_H
#define BUDGET_H

#include <iostream>
#include <vector>
#include <fstream>
#include "income.h"
#include "expense.h"
#include "Markup.h"

using namespace std;

class Budget
{
    int idOfTheLoggedUser;
    int numberOfIncomes;
    int numberOfExpenses;

public:
    Budget();
    int getIdOfTheLoggedUser();
    void setIdOfTheLoggedUser(int idOfTheLoggedUser);
    int getNumberOfIncomes();
    void setNumberOfIncomes(int numberOfIncomes);
    int getNumberOfExpenses();
    void setNumberOfExpenses(int numberOfExpenses);
    void addIncome();
    void addExpense();
    void showBalance(vector<Income> &incomes, vector<Expense> &expenses);

private:
    void loadDataFromFile(vector<Income> &incomes, vector<Expense> &expenses, int idOfTheLoggedUser);
    void createAFileIfItdoesNotExist(string fileName);
};

#endif

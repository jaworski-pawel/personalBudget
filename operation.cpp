#include <iostream>
#include "operation.h"

using namespace std;

Operation::Operation(int operationId, int userId, int date, string item, double amount)
{
    this -> operationId = operationId;
    this -> userId = userId;
    this -> date = date;
    this -> item = item;
    this -> amount = amount;
}

int Operation::getOperationId()
{
    return operationId;
}

void Operation::setOperationId(int operationId)
{
    this -> operationId = operationId;
}

int Operation::getUserId()
{
    return userId;
}

void Operation::setUserId(int userId)
{
    this -> userId = userId;
}

int Operation::getDate()
{
    return date;
}

void Operation::setDate(int date)
{
    this -> date = date;
}

string Operation::getItem()
{
    return item;
}

void Operation::setItem(string item)
{
    this -> item = item;
}

double Operation::getAmount()
{
    return amount;
}

void Operation::setAmount(double amount)
{
    this -> amount = amount;
}



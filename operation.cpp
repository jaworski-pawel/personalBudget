#include <iostream>
#include "operation.h"

using namespace std;

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

float Operation::getAmount()
{
    return amount;
}

void Operation::setAmount(float amount)
{
    this -> amount = amount;
}



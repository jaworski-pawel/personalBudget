#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>

using namespace std;

class Operation
{
    int userId;
    int date;
    string item;
    float amount;

public:
    int getUserId();
    void setUserId(int userId);
    int getDate();
    void setDate(int date);
    string getItem();
    void setItem(string item);
    float getAmount();
    void setAmount(float amount);
};

#endif

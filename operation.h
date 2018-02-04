#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>

using namespace std;

class Operation
{
    int operationId;
    int userId;
    int date;
    string item;
    double amount;

public:
    Operation(int operationId, int userId, int date, string item, double amount);
    int getOperationId();
    void setOperationId(int operationId);
    int getUserId();
    void setUserId(int userId);
    int getDate();
    void setDate(int date);
    string getItem();
    void setItem(string item);
    double getAmount();
    void setAmount(double amount);
};

#endif

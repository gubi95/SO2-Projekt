#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <queue>
#include "Customer.h"

class Checkout
{
    public:
        Checkout();
        Checkout(string strName):Name(strName){};
        string Name;
        queue<Customer> Customers;
};

#endif // CHECKOUT_H

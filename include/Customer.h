#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <list>
#include "WarehouseProduct.h"

class Customer
{
    public:
        Customer();
        Customer(list<WarehouseProduct> listWarehouseProduct): Products(listWarehouseProduct) {};
        list<WarehouseProduct> Products;
};

#endif // CUSTOMER_H
